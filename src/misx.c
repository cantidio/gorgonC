/**
 * função para calcular o tamanho de um arquivo
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 06/06/2008
 * @final: 06/06/2008
 * @param: char *, nome do arquivo a ser calculado o tamanho
 * @return: long
 */
long gorgonFileSize(char *filename)
{
	FILE *f;
	f=fopen(filename,"r");
	if(f!=NULL)
	{
		fseek(f,0,SEEK_END);
		return ftell(f);
	}
	return 0;
}
