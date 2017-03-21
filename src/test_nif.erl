-module(test_nif).
-on_load(load_nif/0).

-compile(export_all).

load_nif() ->
    Path = case code:priv_dir(?MODULE) of
        {error, _} ->
            EbinDir = filename:dirname(code:which(?MODULE)),
            AppPath = filename:dirname(EbinDir),
            filename:join(AppPath, "priv");
        P ->
            P
    end,
    FullPath = filename:join([Path, "test_nif"]),
    erlang:load_nif(FullPath, 0).

%/* Library lifetime */
spawn_pthread() -> "NIF library not loaded".
