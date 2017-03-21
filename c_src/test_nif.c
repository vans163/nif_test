#include "erl_nif.h"

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

pthread_t g_Thread;
static ErlNifPid my_pid;

ERL_NIF_TERM mk_atom(ErlNifEnv* env, const char* atom)
{
    ERL_NIF_TERM ret;
    if(!enif_make_existing_atom(env, atom, &ret, ERL_NIF_LATIN1))
        return enif_make_atom(env, atom);
    return ret;
}

void* thread_func(void* context) {
    ErlNifEnv* msg_env = enif_alloc_env();
    enif_send(NULL, &my_pid, msg_env, enif_make_int(msg_env, 55));    
    enif_free_env(msg_env);

    msg_env = enif_alloc_env();
    enif_send(NULL, &my_pid, msg_env, enif_make_int(msg_env, 55));    
    enif_free_env(msg_env);

    msg_env = enif_alloc_env();
    enif_send(NULL, &my_pid, msg_env, enif_make_int(msg_env, 56));    
    enif_free_env(msg_env);

    return NULL;
}

static ERL_NIF_TERM spawn_pthread(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    enif_self(env, &my_pid);
    pthread_create(&g_Thread, NULL, &thread_func, NULL);
    return mk_atom(env, "ok");
}

int upgrade(ErlNifEnv* env, void** priv_data, void** old_priv_data, ERL_NIF_TERM load_info)
{
    return 0;
}

static ErlNifFunc nif_funcs[] = {
    {"spawn_pthread", 0, spawn_pthread},
};

ERL_NIF_INIT(test_nif, nif_funcs, NULL, NULL, &upgrade, NULL)
