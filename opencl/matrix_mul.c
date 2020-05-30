/*

clang -framework OpenCL matrix_mul.c -w
./a.out

*/

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#endif
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 2048
#define ERROR -1

#define END 0

char *KernelSource = "";

char* read_file(char* filename, int* len) {
    int ip_file, rd_cnt, tot_cnt = 0;
    int buf_size = BUF_SIZE;
    char * tmp_buf = malloc(buf_size * sizeof(char));
    char * offset = tmp_buf;
    ip_file = open(filename, O_RDONLY);
    if (ip_file == ERROR) {
        perror("Error accessing file.");
        return (char*)-1;
    }
    do {
        rd_cnt = read(ip_file,offset,BUF_SIZE);
        offset += rd_cnt;
        tot_cnt += rd_cnt;
    }while(rd_cnt != END);
    (*len) = tot_cnt;
    return tmp_buf;
}

const char *getErrorString(cl_int error)
{
  switch(error){
      case 0: return "CL_SUCCESS";
    }
}

void printMatrix(int *arr, int n, int m) {
  int i, j;
  for (i = 0 ; i < n ; ++i ) {
    for (j = 0 ; j < m ; ++j ) {
        printf("%d ", arr[i*n+j]);
    }
    printf("\n" );
  }
  printf("\n" );
}

int main(int argc, char const *argv[]) {
  cl_platform_id platform_id;
  cl_uint num_of_platforms;
  cl_device_id device_id;
  cl_uint num_of_devices;
  cl_context context;
  cl_context_properties properties[3];
  cl_kernel kernel;
  cl_command_queue command_queue;
  cl_int err;
  cl_program program;
  cl_mem inputA, inputB, output;
  size_t local[2], global[2];
  int len;
  int res;
  int n = 3;
  int inp_len = sizeof(int)*n*n, op_len = sizeof(int)*n*n;
  int matA[] = {1,2,3,4,5,6,7,8,9};
  int matB[] = {5,4,3,2,1,9,8,7,6};
  int matC[9];

  printMatrix(matA,n,n);
  printMatrix(matB,n,n);

  KernelSource = read_file("matrix_mul.cl",&len);

  if (clGetPlatformIDs(1,&platform_id,&num_of_platforms) != CL_SUCCESS) {
    printf("Platform ID Error\n");
    return -1;
  }

  if (clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_ALL,1,&device_id,&num_of_devices)) {
    printf("Device ID error\n");
    return -1;
  }


  properties[0] = CL_CONTEXT_PLATFORM;
  properties[1] = (cl_context_properties) platform_id;
  properties[2] = 0;

  context = clCreateContext(properties,1,&device_id,NULL,NULL,&err);

  command_queue = clCreateCommandQueue(context,device_id,0,&err);

  inputA = clCreateBuffer(context,CL_MEM_READ_ONLY,inp_len,NULL,&err);
  if (err < 0)
    printf("Create buffer Error: %s\n",getErrorString(err));
  inputB = clCreateBuffer(context,CL_MEM_READ_ONLY,inp_len,NULL,&err);
  if (err < 0)
    printf("Create buffer Error: %s\n",getErrorString(err));
  output = clCreateBuffer(context,CL_MEM_WRITE_ONLY,op_len,NULL,&err);
  if (err < 0)
    printf("Create buffer Error: %s\n",getErrorString(err));

  clEnqueueWriteBuffer(command_queue,inputA,CL_TRUE,0,inp_len,matA,0,NULL,NULL);
  clEnqueueWriteBuffer(command_queue,inputB,CL_TRUE,0,inp_len,matB,0,NULL,NULL);

  program = clCreateProgramWithSource(context,1,(const char**) &KernelSource, NULL, &err);

  if (res = clBuildProgram(program,1,&device_id,NULL,NULL,NULL) != CL_SUCCESS) {
    printf("Error building program: %s\n",getErrorString(res));
    return -1;
  }

  kernel = clCreateKernel(program,"mat_mul",&err);
  if (err < 0)
    printf("Create buffer Error: %s\n",getErrorString(err) );

  if (clSetKernelArg(kernel,0,sizeof(cl_mem),&inputA) != CL_SUCCESS) {
    printf("Kernell setting error\n");
  }
  if (clSetKernelArg(kernel,1,sizeof(cl_mem),&inputB) != CL_SUCCESS) {
    printf("Kernell setting error\n");
  }
  if (clSetKernelArg(kernel,2,sizeof(cl_mem),&output) != CL_SUCCESS) {
    printf("Kernell setting error\n");
  }

  global[0] = 3;
  global[1] = 3;

  if(clEnqueueNDRangeKernel(command_queue,kernel,2,NULL,global,NULL,0,NULL,NULL) != CL_SUCCESS ) {
    printf("Enque error\n");
    return -1;
  }

  if(clEnqueueReadBuffer(command_queue,output,CL_TRUE,0,op_len,matC,0,NULL,NULL) != CL_SUCCESS ) {
    printf("Buffer read error\n");
    return -1;
  }

  printMatrix(matC,n,n);

  return 0;
}