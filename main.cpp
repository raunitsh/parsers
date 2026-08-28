#include "Loader.hpp"
#include "JSONParser.hpp"

int
main ()
{
        Loader loader;
        RString path;
        bool rc;

    path.SetString ("../test.json");

    loader.OpenFileRO ();
    
    rc = loader.ParseFile<JSONParser> ();
    
    printf ("%d\n", rc);
    
    return 0;
}