#include "driver.h"
#include "symTable.c"


//Shared Variables
FILE *yyin;
FILE *lexFile;
FILE *parseFile;
FILE *symbolTableFile;
int parseDebug = 0;
int lexDebug = 0;
int symbolTableDebug = 0;

int rowNum = 1;
int tabSize = 4;
int column = 0;

char * buffer;
long bufferSize;
bool lookUpMode = 0; 

node * symbolTable;
treeNode* currentIdentifier;
flagContainer flags;
flagContainer reset;

int main(int argc, char **argv)
{

  //Declerations
  int options = 0;
  FILE * testFile;
  
    testFile = fopen(argv[1], "r");
    if (!testFile) {
	    printf("Error opening Test File!\n");
	    return -1;
    }
    
  
    //Read testFile into a buffer
    
        fseek( testFile , 0L , SEEK_END);
        bufferSize = ftell( testFile );
        rewind( testFile );

        /* allocate memory for entire content */
        buffer = calloc( 1, bufferSize+1 );
        if( !buffer ) fclose(testFile),fputs("memory alloc fails",stderr),exit(1);

        /* copy the file into the buffer */
        if( 1!=fread( buffer , bufferSize, 1 , testFile) )
          fclose(testFile),free(buffer),fputs("entire read fails",stderr),exit(1);

        /* do your work here, buffer is a string contains the whole text */

        fclose(testFile);
    
            
    testFile = fopen(argv[1], "r");
  //Initiate SymTable
  symbolTable = createTable(symbolTable);
  symbolTable = pushLevel(symbolTable,0);
  

  
  
  
  //Parse the command line for debugging options
  while ((options = getopt (argc, argv, "-d[lsp]")) != -1){ 
    switch (options)
      {
      case 'l':
        lexDebug = 1;
        lexFile = fopen("lexOutput.txt", "w");
        break;
      case 's':
        symbolTableDebug = 1;
        symbolTableFile = fopen("symbolTableOutput.txt", "w");
        break;
      case 'p':
        parseDebug = 1;
        parseFile = fopen("parserOutput.txt", "w");
        break;

      }
      
     } 


  
    
	// set lex to read from it instead of defaulting to STDIN:
	yyin = testFile;
	// parse through the input until there is no more:
    yyparse(); 
	
    fclose(testFile); 
    
    if(parseDebug)
        fclose(parseFile);
        
    if(lexDebug)
        fclose(lexFile);
        
    if(symbolTableDebug)
    {
        printTable(symbolTable);
        fclose(symbolTableFile);
        
    }
    
    free(buffer);
        	  
	
}


 
 

