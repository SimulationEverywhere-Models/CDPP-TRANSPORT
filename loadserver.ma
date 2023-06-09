[top]
components : loadser@Loadserver
out : exitload
out : readyaccept
in: enterload
Link : enterload enterload@loadser
Link : exitload@loadser exitload
Link : readyaccept@loadser readyaccept

[loadser]
distribution : normal
mean : 180
deviation : 20 