/*execute.h*/

/**
  * @brief Executes nuPython program, given as a Program Graph.
  *
  * @note Prof. Joe Hummel
  * @note Northwestern University
  */

#pragma once

#include "programgraph.h"
#include "ram.h"

//
// Public functions:
//

/**
 * @brief executes a nuPython expression
 *
 * Given an expression such as x * y or a > b, executes
 * the expression and returns the result as a RAM_VALUE.
 * If the execution fails with a semantic error, an
 * error message is output and NULL is returned.
 *
 * NOTE: this function allocates memory for the value that
 * is returned. This implies if the return value != NULL, 
 * the caller takes ownership of the copy and must
 * eventually free this memory via ram_free_value().
 *
 * @param program pointer to a stmt in program graph
 * @param memory pointer to memory unit
 * @param pointer to expression to execute
 * @return pointer to RAM_VALUE containing result of evaluating
 *         expression, or NULL if a semantic error
 */
struct RAM_VALUE* execute_expr(struct STMT* stmt, struct RAM* memory, struct EXPR* expr);

/**
 * @brief executes a nuPython program
 *
 * Given a nuPython program graph and a memory, 
 * executes the statements in the program graph.
 * If a semantic error occurs (e.g. type error),
 * an error message is output, execution stops,
 * and the function returns {false, pointer to
 * statement where the error occurred}.
 *
 * If the program executes successfully, {true,
 * pointer to last stmt executed} is returned.
 *
 * @param program pointer to first stmt in program graph
 * @param memory pointer to memory unit
 * @return ExecuteResult
 */
 
struct ExecuteResult {
  bool         Success;   // true -> success
  struct STMT* LastStmt;  // ptr to last stmt executed
};

struct ExecuteResult execute(struct STMT* program, struct RAM* memory);
