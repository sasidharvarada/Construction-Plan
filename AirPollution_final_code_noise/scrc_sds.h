/*
 * scrc_sds.h
 *
 *  Created on: 16-Oct-2020
 *      Author: BSRC-Sam
  *  last update :22-08-2023
 *      Author : SCRC-Sasidhar
 */

#ifndef INCLUDE_SCRC_SDS_H_
#define INCLUDE_SCRC_SDS_H_

extern float p25;
extern float p10;

void hw_setup_sds();
void hw_read_sds(float *buf_pm25, float *buf_pm25cal,float *buf_pm10, float *buf_pm10cal);

#endif /* INCLUDE_SCRC_SDS_H_ */
