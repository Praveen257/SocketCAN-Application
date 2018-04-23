/* Header file for the project "MOBILE PLATTFORM 		*/


#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <string.h>


#define Buf_Max 500			/* maximum size of the record buffer */

struct Cluster{
	int near_target;
	int far_target;
	int cycle_counter;
	int interface;
};

struct Cluster_GenInf{
	int clust_id;
	int clust_distlong;
	int clust_distlat;
	int clust_vrelLong;
	int clust_vrelLat;
	int clust_dycprop;
	int clust_RCS;
};

#define Cluster_stat 0x600
/* Definitions for Cluster genral information*/
#define Cluster_Gen 0x701
#define scal_dist 0.2
#define scal_vrel 0.25
#define offst_dtlong -500
#define offst_dtlat -102.3
#define offst_vrellong -128
#define offst_vrellat -64
#define offst_rcs -64


#define d1 0.0
#define d2 0.0
#define c1 0.0
#define c2 0.0


extern int open_socket(int *socket_id);
extern void Read_Cluster(int socket_id, struct Cluster *Cluster_ptr);
extern void Read_ClusterGen(int socket_id, struct Cluster_GenInf *Cluster_ptr);
