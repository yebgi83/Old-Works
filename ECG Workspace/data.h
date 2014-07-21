#define DATA( a, b )   a.pData[b]
#define SIZE( a )      a.Size


typedef struct InData
{ 
    short Used;          
    short Size;
    short *pData;
};

short LoadInput( InData *pID, char *filename )
{
    std::ifstream ifs;
    short size;

    printf("Loading %s.\n", filename);
    ifs.open( filename );
    if( ifs.fail() )
    {
        printf("Error : %s is not found.\n");
        return FALSE;
    }

    ifs >> size;
    if( size == 0 )
    {
        printf("Error : Loading data is empty.\n");
        ifs.close();
        return FALSE;
    }
    
    if( pID->Used == FALSE )
    {
        pID->pData = new short [size];
        if( pID->pData == NULL )
        {
            printf("Error : Allocation failed.\n");
            ifs.close();
            return FALSE;
        }
        else
        {
            pID->Used = TRUE;
            printf("%d Units Allocated.\n", size);
        }
        pID->Size = size;
    }
    else
    {
        // pID->Used == TRUEÀÏ¶§
        delete pID->pData;
        pID->Used = FALSE;
        pID->Size = 0;
        printf("Data block Unallocated.\n");
        
        pID->pData = new short [size];
        if( pID->pData == NULL )
        {
            printf("Error : Allocation failed.\n");
            ifs.close();
            return FALSE;
        }
        else
        {
            pID->Used = TRUE;
            printf("%d Units Allocated.\n" );
        }
        pID->Size = size;
    }

    for( int c = 0; c < size ; c++ )
        ifs >> pID->pData[c];
 
    printf("Load Completed.\n");
    ifs.close();
    
    return TRUE;
}
