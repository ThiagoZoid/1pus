//Entidade do ouro.
#define goldEntity (Entity){ goldID, false, false, goldSprite, NULL, NULL, NULL, NULL, NULL }

//Vari�veis do ouro (marca se o ouro
//j� foi pego e impossibilida o jogador de repetir o processo).
typedef struct goldVars{
    bool taken;
} GoldVars;

//Inicializa as vari�veis padr�o do ouro.
GoldVars *default_gold_vars(){
    GoldVars *vars = (GoldVars*)malloc(sizeof(GoldVars));
    vars->taken = false;
    return vars;
}
