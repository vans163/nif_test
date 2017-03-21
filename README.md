# nif_test
testing for different things

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
