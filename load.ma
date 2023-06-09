[top]
components : loadque@Loadqueue loadser@Loadserver 
out : exitload
in : arriveload
Link : arriveload arriveload@loadque
Link : readygoload@loadque enterload@loadser
Link : readyaccept@loadser loaddone@loadque
Link : exitload@loadser exitload


[loadque]
preparation : 00:00:10:000 

[loadser]
distribution : normal
mean : 180
deviation : 0 

