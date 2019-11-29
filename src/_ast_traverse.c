#include <parser.h>
#include <vector.h>
#include <ir.h>

void ast_traverse_template(kx_object_t *node, kx_context_t *ctx)
{
    switch (node->type) {
    case KXVL_UNKNOWN:
    case KXVL_INT:
    case KXVL_DBL:
    case KXVL_STR:
    case KXVL_NULL:
    case KXVL_TRUE:
    case KXVL_FALSE:

    case KX_VAR:
    case KX_KEYVALUE:

    case KXOP_POSITIVE:
    case KXOP_NEGATIVE:
    case KXOP_INC:
    case KXOP_DEC:
    case KXOP_INCP:       /* postfix */
    case KXOP_DECP:       /* postfix */

    case KXOP_ASSIGN:
    case KXOP_ASSIGN_ADD:
    case KXOP_ASSIGN_SUB:
    case KXOP_ASSIGN_MUL:
    case KXOP_ASSIGN_DIV:
    case KXOP_ASSIGN_MOD:
    case KXOP_ASSIGN_AND:
    case KXOP_ASSIGN_OR:
    case KXOP_ASSIGN_XOR:
    case KXOP_ASSIGN_LAND:
    case KXOP_ASSIGN_LOR:
    case KXOP_ADD:
    case KXOP_SUB:
    case KXOP_MUL:
    case KXOP_DIV:
    case KXOP_MOD:
    case KXOP_AND:
    case KXOP_OR:
    case KXOP_XOR:
    case KXOP_LAND:
    case KXOP_LOR:
    case KXOP_EQEQ:
    case KXOP_NEQ:
    case KXOP_LE:
    case KXOP_LT:
    case KXOP_GE:
    case KXOP_GT:
    case KXOP_LGE:
    case KXOP_CALL:

    case KXOP_TER:

    case KXST_EXPR:       /* lhs: expr */
    case KXST_EXPRLIST:   /* lhs: expr1: rhs: expr2 */
    case KXST_STMTLIST:   /* lhs: stmt1: rhs: stmt2 */
    case KXST_IF:         /* lhs: cond, rhs: then-block: ex: else-block */
    case KXST_WHILE:      /* lhs: cond: rhs: block */
    case KXST_DO:         /* lhs: cond: rhs: block */
    case KXST_FOR:        /* lhs: forcond: rhs: block */
    case KXST_FORCOND:    /* lhs: init, rhs: cond: ex: inc */
    case KXST_TRY:        /* lhs: try, rhs: catch: ex: finally */
    case KXST_CATCH:      /* lhs: name: rhs: block */
    case KXST_RET:        /* lhs: expr */
    case KXST_THROW:      /* lhs: expr */
    case KXST_CLASS:      /* s: name, lhs: arglist, rhs: block: ex: expr (inherit) */
    case KXST_FUNCTION:   /* s: name, lhs: arglist, rhs: block: optional: public/private/protected */
    default:
        break;
    }
}
