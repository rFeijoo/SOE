```
1. Por que o Linux recebeu esse nome?
   O nome faz referência ao seu criador, Linus Torvalds, ao mesmo tempo em que ao free-software Unix.
```
```
2. O que são daemons?
   Daemons são processos que rodam em plano de fundo, principalmente, para iniciar, reiniciar, parar, entre outras. São exemplos: abrir porta de rede, monitoramento do disco rígido e rodar tasks programadas.
```
```
3. O que é o shell?
   É a interface entre o sistema operacional e o usuário, capaz de ler e interpretar comandos além de retornar resultados.
```
```
4. Por que é importante evitar executar o terminal como super-usuário?
   Com super-usuário é possível acessar todo e qualquer arquivo do sistema operacional, bem como edita-lo e escluí-lo. Dessa forma, torna-se arriscado dar esse tipo de acesso pois o pode haver perda de arquivos importantes ou mesmo o corrompimento do sistema operacional.
```
```
5. Qual botão do teclado completa o que o usuário escreve no terminal, de acordo com o contexto?
   TAB
```
```
6. Quais botões do teclado apresentam instruções escritas anteriormente?
   Up Arrow & Down Arrow
```
```
7. Apresente os respectivos comandos no terminal para:
	(a) Obter mais informações sobre um comando.
	    "man ascii", para saber mais sobre a ascii table
	    
        (b) Apresentar uma lista com os arquivos dentro de uma pasta.
	    "ls"
	    
	(c) Apresentar o caminho completo da pasta.
	    "pwd"
	    
	(d) Trocar de pasta.
	    "cd outra_pasta", para mudar para a pasta "outra_pasta"
	    
	(e) Criar uma pasta.
	    "mkdir nova", para criar a pasta "nova"
	    
	(f) Apagar arquivos definitivamente.
	    "rm -R text.txt", para apagar o arquivo "text.txt"
	    
	(g) Apagar pastas definitivamente.
	    "rmdir dir", para apagar a pasta "dir"
	    
	(h) Copiar arquivos.
	    "cp fileName.md newFile.md", para criar uma cópia do arquivo "fileName.md" chamado "newFile.md"
	    
	(i) Copiar pastas.
	    "cp -r dir newDir", para criar uma cópia da pasta "dir" chamada "newDir" no mesmo diretório
	    
	(j) Mover arquivos.
	    "mv file.txt ..", para mover o arquivo "file.txt" para o diretório anterior
	    
	(k) Mover pastas.
	    "mv dir ..", para mover a pasta "dir" para o diretório anterior
	    
	(l) Renomear pastas.
	    "mv dir newDir", para renomear a pasta "dir" para "newDir"
	    
	(m) Apresentar o conteúdo de um arquivo.
	    "cat file.txt", para apresentar o conteúdo do arquivo "file.txt"
	    
	(n) Apresentar o tipo de um arquivo.
	    "file text.txt", para apresentar o tipo do arquivo "text.txt"
	    
	(o) Limpar a tela do terminal.
	    "clear"
	    
	(p) Encontrar ocorrências de palavras-chave em um arquivo-texto.
	    "grep -ic "Linux" 02_Intro_Linux_1.md", para procurar pela palavra "Linux", case-insensitive (-i), no arquivo "02_Intro_Linux_1.md". O resultado mostra a quantidade matches.
	    
	(q) Ordenar informações em um arquivo-texto.
	    "sort names.txt", para ordenar em ordem alfabética o arquivo "names.txt"
	    
	(r) Substituir ocorrências de palavras-chave em um arquivo-texto.
	    "sed 's/word/newWord/g' file.txt", substitui a palavra "word" pela palavra "newWord" no arquivo "file.txt"
	    
	(s) Conferir se dois arquivos são iguais.
	    "diff file1.txt file2.txt", escreverá na tela todo conteúdo que diferencia os arquivos. Caso eles sejam iguais, não haverá output.
	    
	(t) Escrever algo na tela.
	    "echo "hello world"", para escrever "hello world" no console
```
