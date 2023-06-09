[top]
components : unloadser@Unloadserver
out : exitunload readyreceive
in: enterunload
Link : enterunload enterunload@unloadser
Link : exitunload@unloadser exitunload
Link : readyreceive@unloadser readyreceive

[unloadser]
distribution : normal
mean : 120
deviation : 10 