/*
 * formatter.c
 *
 *  Created on: 23/08/2013
 *      Author: phm
 */
#include <stdio.h>
#include <stdlib.h>
#include "formatter.h"

/*
 * Protected Methods
 */
void formatter_preamble_(formatter *cthis, char* string);
void formatter_postamble_(formatter *cthis, char* string);

/*
 * HTML sub-class of formatter class
 */

void html_preamble_(formatter *cthis, char* string){
  char html_start[]= {"<!DOCTYPE html>"};
  char html_header_start[]={"<HEAD>\n<TITLE>\n"};
  char html_header_end[]={"</TITLE>\n</HEAD>\n"};
  char html_body_start[]={"<BODY>\n"};

  fprintf(cthis->fp, "%s", html_start);
  fprintf(cthis->fp, "%s", html_header_start);
  fprintf(cthis->fp, "%s\n", string);
  fprintf(cthis->fp, "%s", html_header_end);
  fprintf(cthis->fp, "%s", html_body_start);
}

void html_postamble_(formatter *cthis, char* string){
  char html_body_end[]={"</BODY>\n"};
  char html_end[]={"</HTML>\n"};
  fprintf(cthis->fp, "%s", html_body_end);
  fprintf(cthis->fp, "%s", html_end);
}

void html_header_(formatter *cthis, char* string){
  fprintf(cthis->fp, "<H1>%s</H1>\n", string);
}

void html_body_(formatter *cthis, char* string){
  fprintf(cthis->fp, "<P>%s</P>\n", string);
}

/*
 * TEXT sub-class of formatter class
 */

void text_preamble_(formatter *cthis, char* string){
  fprintf(cthis->fp, "%s%s%s", "#### Start File: ", string, " #### \n\n================================================\n\n");
}

void text_header_(formatter *cthis, char* string){
  fprintf(cthis->fp, "%s%s", string, "\n\n================================================\n\n");
}

void text_body_(formatter *cthis, char* string){
  fprintf(cthis->fp, "%s%s", string, "\n\n------------------------------------------------");
}

void text_postamble_(formatter *cthis, char* string){
  fprintf(cthis->fp, "%s%s%s", "\n\n#### End File: ", string, " ####");
}
/*
 * Formatter class Constructor & Destructor
 */

void formatter_init(formatter *cthis, formatter_strategy strategy, char *pathname){

  char fullpathname[255];
  switch(strategy) {
    case HTML:
      puts("Formatting HTML\n");
      
      cthis->formatter_header = html_header_;
      cthis->formatter_body = html_body_;
      cthis->formatter_preamble_ = html_preamble_;
      cthis->formatter_postamble_ = html_postamble_;

      sprintf(fullpathname, "%s.html", pathname);
      break;
    case TEXT:
      puts("Formatting TXT\n");

      cthis->formatter_header = text_header_;
      cthis->formatter_body = text_body_;
      cthis->formatter_preamble_ = text_preamble_;
      cthis->formatter_postamble_ = text_postamble_;
      
      sprintf(fullpathname, "%s.txt", pathname);
      break;
    default:
      break;
  }

  cthis->fp = fopen(fullpathname, "w");
  if(cthis->fp <= 0){
    printf("Invalid file pointer!\n");
    exit(0);
  }
  formatter_preamble_(cthis, fullpathname);
}

void formatter_release(formatter *cthis){
  formatter_postamble_(cthis, "Thanks Folks!");
  fclose(cthis->fp);
}

/*
 * Formatter class public methods 
 * (Prototypes are placed in formatter.h)
 */

void formatter_header(formatter *cthis, char* string){
  cthis->formatter_header(cthis, string);
}

void formatter_body(formatter *cthis, char* string){
  cthis->formatter_body(cthis, string);
}

void formatter_preamble_(formatter *cthis, char* string){
  cthis->formatter_preamble_(cthis, string);
}

void formatter_postamble_(formatter *cthis, char* string){
  cthis->formatter_postamble_(cthis, string);
}
