/*
 * scrc_noise.h
 *
 *  Created on: 16-Oct-2020
 *      Author: BSRC-Sam
 *  Last update: 20-08-2024
 *      Author: SCRC-Sasidhar
 */

#ifndef INCLUDE_SCRC_NOISE_H_
#define INCLUDE_SCRC_NOISE_H_

void hw_setup_noise();
void hw_read_noise(float *buf_dbValue,float *buf_dbValue_cal);

#endif /* INCLUDE_SCRC_NOISE_H_ */
