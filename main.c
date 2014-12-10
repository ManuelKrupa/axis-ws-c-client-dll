#include "main.h"
#include "axis2_stub_AdditionServiceService.h"

#include <stdio.h>
#include <axiom.h>
#include <axis2_util.h>
#include <axiom_soap.h>
#include <axis2_client.h>

int getSum(const axutil_env_t *env, axis2_stub_t *stub, int nb_1, int nb_2);

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

int __stdcall fnSomme(int a, int b)
{
    /** the core variables */
    axutil_env_t *env = NULL;
    axis2_char_t *client_home = NULL;
    axis2_char_t *endpoint_uri = NULL;
    axis2_stub_t *stub = NULL;

    /* steps to create the stub */ 
    endpoint_uri = "http://localhost:9090/axiswstest/AdditionService";
    env = axutil_env_create_all("alltest.log", AXIS2_LOG_LEVEL_TRACE);
    client_home = AXIS2_GETENV("AXIS2C_HOME");

    stub = axis2_stub_create_AdditionServiceService(env, client_home, endpoint_uri);

    if(stub)
    {
        /* call the method that actually invoke the service written below */ 
        return getSum(env, stub, a, b);
    }
    return -1;
}

int getSum(const axutil_env_t *env, axis2_stub_t *stub, int nb_1, int nb_2)
{
    
    adb_addition_t *request;
    adb_additionResponse_t *response;
    int sum;
    
    /* Build the request adb */
    request = adb_addition_create(env);
    if(request == NULL)
    {
		printf("request creation impossible");
	    return -1;
    }
    adb_addition_set_a(request, env, nb_1);
    adb_addition_set_b(request, env, nb_2);

    /* Finished building the request, time to call the service */
    response = axis2_stub_op_AdditionServiceService_addition(stub, env, request);
    
   sum = adb_additionResponse_get_additionReturn(response, env);
   printf("Returned Sum: %d\n", sum);
   return sum;
}
