/*
 * scrc_aql.h
 *
 *  Created on: 16-Oct-2020
 *      Author: BSRC-Sam
  *  last update :22-08-2023
 *      Author : SCRC-Sasidhar
 */

#ifndef INCLUDE_SCRC_AQL_H_
#define INCLUDE_SCRC_AQL_H_

enum levels {
	Good, Satisfactory, Moderate, Poor, Very_Poor, Severe, Unknown
};
enum aq {
	pm25_cal_enum, pm10_cal_enum
};

short int aql(float pm);
short int aqi_mp(float pm25_cal, float pm10_cal);
float compute_index_aqi(float pm25_cal, float pm10_cal);

#endif /* INCLUDE_SCRC_AQL_H_ */
