# nif_test
testing for different things

```
erl -eval '{ok, Version} = file:read_file(filename:join([code:root_dir(), "releases", erlang:system_info(otp_release), "OTP_VERSION"])), io:fwrite(Version), halt().' -noshell
19.1.2
```

```
rebar3 auto

1> test_nif:spawn_pthread().
ok
2> receive X-> X after 1 -> ok end.
55
3> receive X-> X after 1 -> ok end.
55
4> receive X-> X after 1 -> ok end.
ok
``

The 3rd receive should have 56.`
