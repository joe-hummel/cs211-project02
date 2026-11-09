/*pgutil.c*/

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

#include <iostream>

using std::cout;
using std::endl;

#include "pgutil.h"


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
struct PG_LINKS break_pg(struct STMT* cur)
{
  struct PG_LINKS links;

  links.next = nullptr;
  links.loop_body = nullptr;
  links.true_path = nullptr;
  links.false_path = nullptr;

  //
  // TODO:
  //
  
  return links;
}


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
void repair_pg(struct STMT* cur, struct PG_LINKS links)
{
  //
  // TODO:
  //
  
  return;
}


#ifdef UNIT_TEST
//////////////////////////////////////////////////////////////////////////
// 
// UNIT TESTS for above functions:
//
//////////////////////////////////////////////////////////////////////////

#include "gtest/gtest.h"

//
// Since we are working in C++, we have to tell the
// C++ compiler that the functions in the provided
// nuPython code are C functions:
//
extern "C" {
  #include "tokenqueue.h"
  #include "parser.h"
  #include "programgraph.h"
  #include "ram.h"
  #include "execute.h"
}

TEST(break_repair_pg, assignment)
{
  cout << "**starting" << endl;

  FILE* file;
  char* filename = "__test.py";

  file = fopen(filename, "w");
  fprintf(file, "x = 0\n");
  fprintf(file, "y = 1\n");
  fclose(file);

  file = fopen(filename, "r");
  struct TokenQueue* tokens = parser_parse(file);
  struct STMT* program = programgraph_build(tokens);
  fclose(file);

  struct STMT* stmt2 = program->types.assignment->next_stmt;

  //
  // okay let's break PG at the first stmt:
  //
  cout << "**breaking..." << endl;

  struct PG_LINKS links = break_pg(program);

  ASSERT_EQ(program->types.assignment->next_stmt, nullptr);
  ASSERT_EQ(links.next, stmt2);

  //
  // now let's repair it:
  //
  cout << "**repairing..." << endl;

  repair_pg(program, links);

  ASSERT_EQ(program->types.assignment->next_stmt, stmt2);

  //
  // done!
  //
  tokenqueue_destroy(tokens);
  programgraph_destroy(program);

  cout << "**passed!" << endl;
}  

TEST(break_repair_pg, pass)
{
  cout << "**starting" << endl;

  FILE* file;
  char* filename = "__test.py";

  file = fopen(filename, "w");
  fprintf(file, "pass\n");
  fprintf(file, "y = 1\n");
  fclose(file);

  file = fopen(filename, "r");
  struct TokenQueue* tokens = parser_parse(file);
  struct STMT* program = programgraph_build(tokens);
  fclose(file);

  struct STMT* stmt2 = program->types.pass->next_stmt;

  //
  // okay let's break PG at the first stmt:
  //
  cout << "**breaking..." << endl;

  struct PG_LINKS links = break_pg(program);

  ASSERT_EQ(program->types.pass->next_stmt, nullptr);
  ASSERT_EQ(links.next, stmt2);

  //
  // now let's repair it:
  //
  cout << "**repairing..." << endl;

  repair_pg(program, links);

  ASSERT_EQ(program->types.pass->next_stmt, stmt2);

  //
  // done!
  //
  tokenqueue_destroy(tokens);
  programgraph_destroy(program);

  cout << "**passed!" << endl;
}  


//////////////////////////////////////////////////////////////////////////
// 
// END OF UNIT TESTS
//
//////////////////////////////////////////////////////////////////////////
#endif
