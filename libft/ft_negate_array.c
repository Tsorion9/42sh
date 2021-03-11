void	negate(char arr[256])
{
	int i;

	i = 0;
	while (i < 256)
	{
		arr[i] = !(arr[i]);
		i++;
	}
}
