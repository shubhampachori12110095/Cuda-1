/*
	Operation about the Device properties
*/

#ifndef H_DEVICEPORP_H
#define H_DEVICEPORP_H

#include "cuda_runtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int getDeviceCount()
{
	int m_count;

	cudaError m_cudaError = cudaGetDeviceCount(&m_count);
	if (m_cudaError != cudaSuccess)
	{
		fprintf(stderr, "get Cuda device count failed");
		exit(0);
	}

	return m_count;
}

cudaDeviceProp getDeviceProp(int deviceNum)
{
	cudaDeviceProp m_deviceprop;

	cudaError m_cudaError = cudaGetDeviceProperties(&m_deviceprop, deviceNum);
	if (m_cudaError != cudaSuccess)
	{
		fprintf(stderr, "get Cuda device properties failed");
		exit(0);
	}

	return m_deviceprop;
}

void showDeviceProp()
{
	cudaDeviceProp m_prop;
	int m_count;

	m_count = getDeviceCount();
	for(int i = 0; i < m_count; ++i)
	{
		m_prop = getDeviceProp(i);

		printf("   --- General Information for device %d --- \n", i);
		printf("Name :  %s\n", m_prop.name);
		printf("Compute capability :   %d.%d\n", m_prop.major, m_prop.minor);  //��ʾ�豸�����汾�źʹΰ汾��
		printf("Clock rate : %d\n", m_prop.clockRate);
		printf("Device copy overlap : ");
		if (m_prop.deviceOverlap)
			printf("Enabled\n");
		else
			printf("Disabled\n");
		printf("Kernel execition timeout : ");
		if (m_prop.kernelExecTimeoutEnabled)
			printf("Enabled\n");
		else
			printf("Disabled\n");

		printf("\n");
		printf("   --- Memory Information for device  %d ---\n", i);
		printf("Total global mem : %ld\n", m_prop.totalGlobalMem);
		printf("Total constant Mem : %ld\n", m_prop.totalConstMem);
		printf("Max mem pitch : %ld\n", m_prop.memPitch);
		printf("Texture Alignment : %ld\n", m_prop.textureAlignment);

		printf("\n");
		printf("   --- MP Information for device %d ---\n", i);
		printf("Multiprocessor count : %d\n", m_prop.multiProcessorCount);
		printf("Shared mem per mp : %ld\n", m_prop.sharedMemPerBlock);
		printf("Register per mp : %d\n", m_prop.regsPerBlock);
		printf("Threads in warp : %d\n", m_prop.warpSize);
		printf("Max threads per block : %d\n", m_prop.maxThreadsPerBlock);
		printf("Max thread dimensions : (%d, %d, %d)\n", m_prop.maxThreadsDim[0],
			m_prop.maxThreadsDim[1], m_prop.maxThreadsDim[2]);
		printf("Max grid dimensions :  (%d, %d, %d)\n", m_prop.maxGridSize[0],
			m_prop.maxGridSize[1], m_prop.maxGridSize[2]); 
	}
}

void chooseDeviceForVersion(int m_major, int m_minor)
{
	//�ҳ�����ϣ���豸ӵ�е����ԣ�������Щ������䵽һ��cudaDeviceProp�ṹ��
	cudaDeviceProp m_prop;
	int dev;

	memset(&m_prop, 0, sizeof(cudaDeviceProp));
	m_prop.major = m_major;
	m_prop.minor = m_minor;

	cudaError m_cudaError = cudaGetDevice(&dev);
	if (m_cudaError != cudaSuccess)
	{
		fprintf(stderr, "get Cuda device failed");
		exit(0);
	}
	printf("ID of current CUDA device : %d\n", dev);

	//������ṹ�����󴫵ݸ�cudaChooseDevice
	m_cudaError = cudaChooseDevice(&dev, &m_prop);
	if (m_cudaError != cudaSuccess)
	{
		fprintf(stderr, "Choose Cuda device failed");
		exit(0);
	}
	printf("ID of CUDA device closest to revision %d.%d : %d\n", m_major, m_minor, dev);

	//��ѡ����豸�趨�ɵ�ǰҪʹ�õ��豸
	m_cudaError = cudaSetDevice(dev);
	if (m_cudaError != cudaSuccess)
	{
		fprintf(stderr, "Set Cuda device failed");
		exit(0);
	}
}
#endif /*  H_DEVICEPORP_H   */