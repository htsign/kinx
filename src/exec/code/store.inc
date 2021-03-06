
#define KX_SET_STRING_CHAR(lvalue, v2) \
{ \
    if ((v2)->type == KX_INT_T) { \
        lvalue = (v2)->value.iv; \
    } else if ((v2)->type == KX_CSTR_T) { \
        lvalue = (v2)->value.pv[0]; \
    } else if ((v2)->type == KX_STR_T) { \
        lvalue = ks_string((v2)->value.sv)[0]; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Invalid string character"); \
    } \
} \
/**/

#define KX_SET_BINARY_CHAR(lvalue, v2) \
{ \
    if ((v2)->type == KX_INT_T) { \
        lvalue = ((v2)->value.iv) & 0xFF; \
    } else if ((v2)->type == KX_CSTR_T) { \
        lvalue = (v2)->value.pv[0]; \
    } else if ((v2)->type == KX_STR_T) { \
        lvalue = ks_string((v2)->value.sv)[0]; \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Invalid binary character"); \
    } \
} \
/**/

#define KX_SET_OBJECT_ITEM(v1, v2, pos) \
{ \
    kv_a(kx_val_t, (v1)->ary, pos) = *v2;\
} \
/**/

#define KX_STORE_TO_STRPOS(v1, v2) \
{ \
    kx_val_t *v1v = v1->value.lv; \
    kx_val_t *v2v = v2; \
    if (v1v->type == KX_CSTR_T || v1v->type == KX_STR_T) { \
        if (v1v->type == KX_CSTR_T) { \
            kstr_t *s = allocate_str(ctx); \
            ks_append(s, v1v->value.pv); \
            v1v->type = KX_STR_T; \
            v1v->value.sv = s; \
        } \
        char *pv = ks_string(v1v->value.sv); \
        KX_SET_STRING_CHAR(pv[v1->pos], v2v) \
    } else if (v1v->type == KX_BIN_T) { \
        uint8_t *bin = &kv_A((v1v)->value.bn->bin, 0); \
        KX_SET_BINARY_CHAR(bin[v1->pos], v2v); \
    } else if (v1v->type == KX_OBJ_T) { \
        KX_SET_OBJECT_ITEM(v1v->value.ov, v2v, v1->pos) \
    } else { \
        THROW_SYSTEM_EXCEPTION("SystemException", "Unsupported Operator"); \
    } \
    v1->has_pos = 0; \
} \
/**/

#define KX_STORE_CODE() \
{ \
    kx_val_t *v1 = &kv_pop((ctx)->stack); \
    KEX_SAVE_VARINFO(*(v1->value.lv)); \
    if (v1->has_pos) { \
        KX_STORE_TO_STRPOS(v1, &kv_last((ctx)->stack)); \
    } else { \
        *(v1->value.lv) = kv_last((ctx)->stack); \
    } \
    KEX_RESTORE_VARINFO(*(v1->value.lv)); \
    cur = cur->next; \
} \
/**/

#define KX_STOREV_CODE() \
{ \
    int lex = cur->value1.i; \
    kx_val_t *v = &kv_last((ctx)->stack); \
    if (lex == 0) { \
        KEX_SAVE_VARINFO(kv_A(frmv->v, cur->value2.i)); \
        kv_A(frmv->v, cur->value2.i) = *v; \
        KEX_RESTORE_VARINFO(kv_A(frmv->v, cur->value2.i)); \
    } else if (lex == 1) { \
        KEX_SAVE_VARINFO(kv_A(lexv->v, cur->value2.i)); \
        kv_A(lexv->v, cur->value2.i) = *v; \
        KEX_RESTORE_VARINFO(kv_A(lexv->v, cur->value2.i)); \
    } else { \
        kx_frm_t *lexp = lexv; \
        while (lexp && --lex) { \
            lexp = lexp->lex; \
        } \
        KEX_SAVE_VARINFO(kv_A(lexp ? lexp->v : frmv->v, cur->value2.i)); \
        kv_A(lexp ? lexp->v : frmv->v, cur->value2.i) = *v; \
        KEX_RESTORE_VARINFO(kv_A(lexp ? lexp->v : frmv->v, cur->value2.i)); \
    } \
    if (v->type == KX_STR_T) { \
        const char *pv = ks_string(v->value.sv); \
        v->type = KX_STR_T; \
        v->value.sv = allocate_str(ctx); \
        ks_append(v->value.sv, pv); \
    } else if (v->type == KX_CSTR_T) { \
        const char *pv = v->value.pv; \
        v->type = KX_STR_T; \
        v->value.sv = allocate_str(ctx); \
        ks_append(v->value.sv, pv); \
    } else if (v->type == KX_BIG_T) { \
        v->type = KX_BIG_T; \
        v->value.bz = make_big_alive(ctx, BzCopy(v->value.bz)); \
    } \
    cur = cur->next; \
} \
/**/

#define KX_STOREX_CODE() \
{ \
    kx_val_t *v1 = &kv_pop((ctx)->stack); \
    KEX_SAVE_VARINFO(*(v1->value.lv)); \
    if (v1->has_pos) { \
        KX_STORE_TO_STRPOS(v1, &kv_pop((ctx)->stack)); \
    } else { \
        *(v1->value.lv) = kv_pop((ctx)->stack); \
    } \
    KEX_RESTORE_VARINFO(*(v1->value.lv)); \
    cur = cur->next; \
} \
/**/

#define KX_STOREVX_CODE() \
{ \
    int lex = cur->value1.i; \
    if (lex == 0) { \
        KEX_SAVE_VARINFO(kv_A(frmv->v, cur->value2.i)); \
        kv_A(frmv->v, cur->value2.i) = kv_pop((ctx)->stack); \
        KEX_RESTORE_VARINFO(kv_A(frmv->v, cur->value2.i)); \
    } else if (lex == 1) { \
        KEX_SAVE_VARINFO(kv_A(lexv->v, cur->value2.i)); \
        kv_A(lexv->v, cur->value2.i) = kv_pop((ctx)->stack); \
        KEX_RESTORE_VARINFO(kv_A(lexv->v, cur->value2.i)); \
    } else { \
        kx_frm_t *lexp = lexv; \
        while (lexp && --lex) { \
            lexp = lexp->lex; \
        } \
        KEX_SAVE_VARINFO(kv_A(lexp ? lexp->v : frmv->v, cur->value2.i)); \
        kv_A(lexp ? lexp->v : frmv->v, cur->value2.i) = kv_pop((ctx)->stack); \
        KEX_RESTORE_VARINFO(kv_A(lexp ? lexp->v : frmv->v, cur->value2.i)); \
    } \
    cur = cur->next; \
} \
/**/

