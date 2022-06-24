# Solution of Exercise of Linux

### Varients of <code>cp</code>


* Syntax : <code>cp [options] source desination</code>

  
    * <code>cp -l</code> : link file instead of copying
    * <code>cp -L</code> : follow symbolic link
    * <code>cp -n</code> : no file overite
    * <code>cp -R</code> : recursive copy
    * <code>cp -u</code> : update
    * <code>cp -v</code> : print information message
     * <code>cp -a</code> : archive files
    * <code>cp -f</code> : force copy by removing the designation file if needed
    * <code>cp -i</code> : iteractive - ask before overrite

* Copy sigle file to directory :
    
    <code>cp hello.c temp</code>

* Copy multiple files :

    <code>cp hello.c sum.c temp</code>

* Copy all files :

    <code>cp *.c temp</code>
