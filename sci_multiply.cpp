
extern "C" {
#include "api_scilab.h"
#include "Scierror.h"

int sci_multiply(char *fname, unsigned fname_len)
{
	SciErr sciErr;

	CheckInputArgument(pvApiCtx,2,2);	//checking whether no. of input arguments in the given range
	CheckOutputArgument(pvApiCtx,1,1);      //checking whether no. of output arguments in the given range



	int *im1=NULL;
	int *im2=NULL;

	sciErr=getVarAddressFromPosition(pvApiCtx,1,&im1);				

	if (sciErr.iErr)
	{
		printError(&sciErr,0);
		return 0;

	}


	if ( !isDoubleType(pvApiCtx,im1) || isVarComplex(pvApiCtx,im1) )

	{
		Scierror(999,"%s : Wrong type of input argument #%d:a real matrix expected\n",fname,1);
		return 0;

	}

	
	double *mat1=NULL;
	double *mat2=NULL;

	int r1=0,c1=0;
	int r2=0,c2=0;

	double *mat=NULL;//output will be stored here

	int i=j=k=0;

        sciErr=getMatrixOfDouble(pvApiCtx,im1,&r1,&c1,&mat1);

	if (sciErr.iErr)
	{
		printError(&sciErr,0);
                return 0;
	}


	sciErr=getVarAddressFromPosition(pvApiCtx,2,&im2);

	if (sciErr.iErr)
	{
		printError(&sciErr,0);
		return 0;

	}


	if ( !isDoubleType(pvApiCtx,im2) || isVarComplex(pvApiCtx,im2) )

	{
		Scierror(999,"%s : Wrong type of input argument #%d:a real matrix expected\n",fname,2);
		return 0;

	}


	sciErr=getMatrixOfDouble(pvApiCtx,im2,&r2,&c2,&mat2);

	if (sciErr.iErr)
	{
		printError(&sciErr,0);
                return 0;
	}


	
	if(c1 != r2)
	{

		Scierror(999, "%s:invalid dimensions", fname,1);
		return 0;


	}										

	mat = (double*)malloc(sizeof(double) * c2 * r1);	
		
        for(i=0;i<c2;i++)

        {
                for (j=0;j<r1;j++)							

                {
                        for(k=0;k<r2;k++)

                        {
                                mat[i*r1+j] += (*(mat2+i*r2+k))*(*(mat1+k*r1 +j));
                        }
			
                }
        }


        sciErr= createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,r1,c2,mat);

        free(mat);

        if(sciErr.iErr)

	{
                printError(&sciErr,0);
                return 0;

        }

         AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;

        return 0;

}

}





