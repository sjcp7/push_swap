
int	ps_sqrt(int num)
{
	int	i;
	int	valor;
	int	valor_prev;

	if (num <= 0)
		return (0);
	i = 2;
	while (i * i < num)
		i++;
	if (i * i == num)
		return (i);
	valor = (i * i) - num;
	valor_prev = num - ((i - 1) * (i - 1));
	if (valor_prev > valor)
		return (i);
	return (i - 1);
}
