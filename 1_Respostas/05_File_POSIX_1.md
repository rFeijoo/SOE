```
1. Considerando a biblioteca-padrão da linguagem C, responda:
	(a) Quais são as funções (e seus protótipos) para abrir e fechar arquivos?
	    FILE *fopen(const char *filename, const char *mode);
	    int fclose(FILE *stream);
	    
	(b) Quais são as funções (e seus protótipos) para escrever em arquivos?
	    int fputc(int char, FILE *stream);
	    int fputs(const char *str, FILE *stream);
	    int fprintf(FILE *stream, const char *format);
	    size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
	    
	(c) Quais são as funções (e seus protótipos) para ler arquivos?
	    int  fgetc(FILE *stream);
	    char *fgets(char *str, int n, FILE *stream);
	    int  fscanf(FILE *stream, const char *format);
	    size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
	    
	(d) Quais são as funções (e seus protótipos) para reposicionar um ponteiro para arquivo?
	    int fseek(FILE *stream, long int offset, int whence);
	    void rewind(FILE *stream);
	    
	(e) Quais bibliotecas devem ser incluídas no código para poder utilizar as funções acima?
	    <stdio.h> // Standard input/output
```
```
2. O que é a norma POSIX?
   Portable Operating System Interface é uma família de normas, definidas pelo IEEE, para garantia de compatibilidade entre sistemas operacionais. Seu objetivo é garantir a portabilidade do código-fonte de programas, à fim de garantir a implemtanção das APIs desenvolvidas para qualquer sistema operacional.
```
```
3. Considerando a norma POSIX, responda:
   	(a) Quais são as funções (e seus protótipos) para abrir e fechar arquivos?
	    int open(const char *path, int oflag);
	    int close(int fildes);
	    
	(b) Quais são as funções (e seus protótipos) para escrever em arquivos?
	    ssize_t write(int fildes, const void *buf, size_t nbyte);
	    
	(c) Quais são as funções (e seus protótipos) para ler arquivos?
	    ssize_t read(int fildes, void *buf, size_t nbyte);
	    
	(d) Quais são as funções (e seus protótipos) para reposicionar um ponteiro para arquivo?
	    void *mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);
	    
	(e) Quais bibliotecas devem ser incluídas no código para poder utilizar as funções acima?
	    <fcntl.h> 	// Função "open()"
	    <unistd.h>	// Função "close()", "read()", "write()", "lseek()"
	    <sys/mman.> // Função "mmap()"
```
