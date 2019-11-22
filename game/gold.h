//Entidade do ouro.
#define goldEntity      (Entity){ goldID, false, false, goldSprite, NULL, NULL, NULL, NULL, NULL }

typedef struct goldVars{
    bool taken;
} GoldVars;

//Inicializa as variáveis padrão do ouro.
GoldVars *default_gold_vars(){
    GoldVars *vars = (GoldVars*)malloc(sizeof(GoldVars));
    vars->taken = false;
    return vars;
}
