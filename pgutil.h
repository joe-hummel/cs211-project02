/*pgutil.h*/

/**
  * @brief program graph utility functions
  *
  * @note SOLUTION
  *
  * @author original template by Prof. Joe Hummel
  * @author ?
  * @author ?
  * @author ?  
  * @note Northwestern University
  */

#pragma once

#include <stdio.h>
#include <stdlib.h>

//
// Since we are working in C++, we have to tell the
// C++ compiler that the functions in the provided
// nuPython code are C functions:
//
extern "C" {
  #include "programgraph.h"
}


/**
 * @brief breaks the program graph at the given stmt
 *
 * Breaks the links between the cur statement and the one 
 * that follows; in the case of while loops and if stmts,
 * there are multiple links that must be broken. Returns 
 * a struct that contains copies of all the broken links.
 *
 * NOTE: not all the links in the struct will be valid. For
 * example, if cur denotes a while loop, then only struct.next
 * and struct.loop_body will be valid --- ignore the other
 * links.
 *
 * @param cur denotes stmt where to break program graph
 * @return struct PG_LINKS that contains saved copies of broken links
 */
struct PG_LINKS {
  struct STMT* next;
  struct STMT* loop_body;
  struct STMT* true_path;
  struct STMT* false_path;
};

struct PG_LINKS break_pg(struct STMT* cur);

/**
 * @brief repairs the program graph at the given stmt
 *
 * This function is the counterpart to break_pg by repairing
 * the program graph using the saved links in the given 
 * struct. This function only works if it is called to repair
 * the program graph at the SAME STATEMENT where it was 
 * broken. In other words, cur in this case must denote the 
 * SAME STMT cur in the call to break_pg.
 *
 * NOTE: not all the links in the struct are valid. For
 * example, if cur denotes a while loop, then only struct.next
 * and struct.loop_body will be valid --- ignore the other
 * links.
 *
 * @param cur denotes stmt where to repair program graph
 * @param struct PG_LINKS containing saved copies of broken links
 */
void repair_pg(struct STMT* cur, struct PG_LINKS links);
