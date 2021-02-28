function! ListNormeErrors()

	" Our custom error format
	set errorformat+=%f:%l%m

	echom "Loading norme from formatted.txt"
	" Hard-coded filename.
	laddfile formatted.txt
endfunction
