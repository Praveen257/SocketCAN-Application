

#include "../inc/radar.h"

int open_socket(int *socket_id){

/* Open an existing CAN-Device File and generate a Socket-ID.		*/
/* Function give a -1 back if the device is not existing		*/
/* If the Socket-ID was succsessfully opened the function give a 0 back	*/



	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame_read;
	char *ifname = "can0";

	*socket_id = socket(PF_CAN, SOCK_RAW, CAN_RAW);
//	printf("After Socket Socket = %d \n", *socket_id);
	strcpy(ifr.ifr_name, ifname);
	ioctl(*socket_id, SIOCGIFINDEX, &ifr);
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	bind(*socket_id, (struct sockaddr *)&addr, sizeof(addr));

	return 0;

}

void Read_Cluster(int socket_id, struct Cluster *Cluster_ptr){
/* Read in a Cluster from the CAN id 600. Read in the load of 5 bytes 	*/
/* decode these loads to the input definition of Cluster.		*/
/* Parameter socket_id: Number of the socket file descriptor 		*/
/* Parameter *Cluster_ptr: Reference pointing to the cluster structure  */

	struct can_frame frame_read;
	int nbytes;

	nbytes = read(socket_id, &frame_read, sizeof(struct can_frame));

	if	(frame_read.can_id == Cluster_stat){
		Cluster_ptr->near_target = (int)frame_read.data[0];
		Cluster_ptr->far_target = (int)frame_read.data[1];
		Cluster_ptr->cycle_counter = (int)(frame_read.data[2] * 256 + frame_read.data[3]);
		Cluster_ptr->interface = (int)(frame_read.data[4]);
		Cluster_ptr->interface =Cluster_ptr->interface & 0xf0;
	}

}

  void Read_ClusterGen(int socket_id, struct Cluster_GenInf *Cluster_ptr){
/* Read in Cluster Genral Information form the CAN id 701 */
  struct can_frame frame_read;
  int nbytes;
  nbytes = read(socket_id, &frame_read, sizeof(struct can_frame));

  if (frame_read.can_id == Cluster_Gen){
    Cluster_ptr->clust_id = (int)frame_read.data[0];
    Cluster_ptr->clust_distlong = (int)(frame_read.data[1] * 256 +(frame_read.data[2] >> 3));
    Cluster_ptr->clust_distlat = (int) ((frame_read.data[2] & 0x03) * 256 +  frame_read.data[3]);
    Cluster_ptr->clust_vrelLong = (int)((frame_read.data[4])*256 + (frame_read.data[5] & 0xC0));
    Cluster_ptr->clust_vrelLat = (int)((frame_read.data[5] & 0x3F) + (frame_read.data[6]) & 0xE0);
    Cluster_ptr->clust_dycprop = (int)((frame_read.data[6]) & 0x07);
    Cluster_ptr->clust_RCS = (int) (frame_read.data[7]);

    Cluster_ptr->clust_distlong = (int)  ((Cluster_ptr->clust_distlong * scal_dist) + offst_dtlong);
    Cluster_ptr->clust_distlat = (int) ((Cluster_ptr->clust_distlat* scal_dist)+offst_dtlat);
    Cluster_ptr->clust_vrelLong = (int) ((Cluster_ptr->clust_vrelLong * scal_vrel)+ offst_vrellong);
    Cluster_ptr->clust_vrelLat = (int) ((Cluster_ptr->clust_vrelLat * scal_vrel)+offst_vrellat);
    Cluster_ptr->clust_RCS = (int) ((Cluster_ptr->clust_RCS * 1)+offst_rcs);

  }





}
