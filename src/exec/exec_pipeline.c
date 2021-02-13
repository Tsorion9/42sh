#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "inc21sh.h"
#include "libft.h"
#include "exec.h"
#include "job.h"
#include "expand_pipeline.h"
#include "pipeline_words_to_assignments.h"

static int exec_pipeline_job(t_pipeline *pipeline)
{
	int fd[2];
	int read_fd;
	pid_t last_child;
	int first_iter = 1;

	if (!pipeline)
		exit(last_cmd_status);
	fd[0] = IGNORE_STREAM;
	while (pipeline && pipeline->command)
	{
		read_fd = fd[0];
		fd[1] = IGNORE_STREAM;
		if (pipeline->next)
		{
			pipe(fd);
		}
		last_child = make_child(pipeline->command, read_fd, fd[1], fd[0], first_iter);
		first_iter = 0;
		pipeline = pipeline->next;
	}
	return (wait_all_children(last_child));
}

/*
** Wait for foreground job, from top_level_shell
*/
int wait_fg_job(pid_t job)
{
	int status;
	t_job *j;

	waitpid(job, &status, WUNTRACED);

	j = find_job(job);
	j->state = job_status_to_state(status);
	j->status = status;
	if (WIFSTOPPED(status))
	{
		/* 
		** We have a SIGTSTP-ed jobshell here 
		** It cannot perform any job control in this state.
		*/
		//fprintf(stderr, "Sending SIGCONT\n");
		kill(j->pgid, SIGCONT);
	}
	if (j->state != DONE)
	{
		j->priority = next_priority();
	}
	if (j->state == DONE)
	{
		remove_job(job);
	}

	if ((j = find_job(job)) && interactive_shell)
	{
		tcgetattr(STDIN_FILENO, &(j->tmodes));
	}
	if (interactive_shell)
	{
		/* Put top-level shell to foreground*/
		tcsetpgrp(STDIN_FILENO, getpid());
		set_shell_input_mode();
	}
	return (status);
}

static t_word_list *get_tail(t_word_list *list)
{
	t_word_list *tmp;

	if (list == NULL)
		return (NULL);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static void	redirect_field_splitting(t_redirect **redirect)
{
	char			*file;
	t_redirector	*redirector;

	if ((*redirect) != NULL && (*redirect)->redirector)
	{
		redirector = (*redirect)->redirector;
		file = redirector->filename;
		if (redirector->need_field_split)
			redirector->splitted_filename = field_splitting_list(file);
	}
}

static void	apply_field_splitting_simple_cmd(t_simple_cmd **simple_cmd)
{
	t_word_list *words;
	t_word_list *tail;
	t_word_list *head;
	t_word_list *fields;

	words = (*simple_cmd)->words;
	tail = NULL;
	head = NULL;
	redirect_field_splitting(&(*simple_cmd)->redirects);
	while (words)
	{
		if (words->need_field_split)
		{
			fields = field_splitting_list(words->word);
			if (head == NULL)
			{
				head = fields;
				tail = get_tail(fields);
			}
			else
			{
				tail->next = fields;
				if (fields != NULL)
					tail = get_tail(fields);
			}
		}
		else
		{
			if (head == NULL)
			{
				head = create_word_node(words->word);
				tail = head;
			}
			else
			{
				tail->next = create_word_node(words->word);
				tail = tail->next;
			}
		}
		words = words->next;
	}
	clean_words(&(*simple_cmd)->words);
	(*simple_cmd)->words = head;
}

static void apply_field_splitting(t_command *command)
{
	if (command->cmd_type == SIMPLE_CMD)
		apply_field_splitting_simple_cmd(&command->simple_cmd);
}

void		pipeline_field_splitting(t_pipeline *pipeline)
{
	t_pipeline *tmp;

	tmp = pipeline;
	while (tmp)
	{
		apply_field_splitting(pipeline->command);
		tmp = tmp->next;
	}
}

static void	quote_removal_filename(t_redirect **redirect)
{
	if (*redirect && (*redirect)->redirector->need_quote_rm)
		quote_removal(&((*redirect)->redirector->filename));
}

void	simple_command_quote_removal(t_simple_cmd *cmd)
{
	t_word_list *words;
	t_word_list *assign;

	words = cmd->words;
	assign = cmd->assignments;
	quote_removal_filename(&cmd->redirects);
	while (words)
	{
		if (words->need_quote_rm)
			quote_removal(&words->word);
		words = words->next;
	}
	while (assign)
	{
		if (!assign->need_field_split)
			quote_removal(&assign->word);
		assign = assign->next;
	}
}

static void	command_quote_removal(t_command *command)
{
	if (command->cmd_type == SIMPLE_CMD)
		simple_command_quote_removal(command->simple_cmd);
}

static void pipeline_quote_removal(t_pipeline *pipeline)
{
	t_pipeline *tmp;

	tmp = pipeline;
	while (tmp)
	{
		command_quote_removal(tmp->command);
		tmp = tmp->next;
	}
}

int exec_pipeline(t_pipeline *pipeline)
{
	pid_t job;

	if (expand_pipeline(pipeline) == EXPANSION_FAIL)
		return (1);
	pipeline_words_to_assignments(pipeline);
	pipeline_field_splitting(pipeline);
	pipeline_quote_removal(pipeline);
	if (is_single_builtin(pipeline) || only_assignments(pipeline))
		return (exec_single_builtin(pipeline));
	if (!top_level_shell)
		return (exec_pipeline_job(pipeline));
	job = fork();
	if (job) /* Top-level shell */
	{
		add_job(job, 0, get_pipeline_str(pipeline));
		if (interactive_shell)
		{
			setpgid(job, job);
			tcsetpgrp(STDIN_FILENO, job);
		}
		return (wait_fg_job(job)); /* Job is in foreground */
	}
	else /* Job shell */
	{
		if (interactive_shell)
		{
			setpgid(getpid(), getpid());
			tcsetpgrp(STDIN_FILENO, getpid()); /* We are foreground */
			set_jobshell_signal();
		}
		top_level_shell = 0;
		exit(exec_pipeline_job(pipeline));
	}
}
