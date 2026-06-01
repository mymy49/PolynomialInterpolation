/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#ifndef YSS_MODULE_POLYNOMIAL_INTERPOLATION__H_
#define YSS_MODULE_POLYNOMIAL_INTERPOLATION__H_

#include <stdint.h>

/**
 * @class PolynomialInterpolation
 * @brief A class that implements multi-point segmented (piecewise linear) interpolation.
 * @details This class allows setting up multiple reference coordinate points (ADC input vs. Target value).
 *          It automatically searches for the correct interval interval and computes the interpolated value.
 * 
 * @author Yoon-Ki Hong
 * @date 2026. 06. 01.
 * @version 1.0.0
 */
class PolynomialInterpolation
{
public:
	/**
	 * @brief Constructor to initialize the interpolation table with a maximum number of points.
	 * @param maxPoint The maximum number of coordinate points this instance can hold.
	 */
	PolynomialInterpolation(uint16_t maxPoint);

	/**
	 * @brief Destructor to free dynamically allocated memory for the data points.
	 */
	~PolynomialInterpolation(void);

	/**
	 * @brief Configure or update a specific coordinate point in the interpolation table.
	 * @param num The index of the point to set (0 to maxPoint - 1)
	 * @param value The target output value for this point
	 * @param adc The raw input value (e.g., ADC) for this point
	 */
	void setPoint(uint16_t num, float value, float adc);

	/**
	 * @brief Set the actual number of active coordinate points to be used for calculation.
	 * @param num The number of active working points (must be less than or equal to maxPoint)
	 */
	void setNumberOfPoint(uint16_t num);

	/**
	 * @brief Get the value and ADC coordinate data of a specific point index.
	 * @param num The index of the point to retrieve
	 * @param value Pointer to store the retrieved target value
	 * @param adc Pointer to store the retrieved raw input value
	 */
	void getPoint(uint16_t num, float *value, float *adc);

	/**
	 * @brief Get the number of currently active working points.
	 * @return uint16_t The number of active points
	 */
	uint16_t getNumberOfPoint(void);

	/**
	 * @brief Calculate the interpolated output value based on the multi-point table.
	 * @param adc The current raw input value to be mapped
	 * @return float The calculated/interpolated target value
	 */
	float calculate(float adc);

private :
	uint16_t mMaxPoint;      ///< Maximum capacity of points allocated in memory
	uint16_t mWorkingPoint;  ///< Number of currently active points used for calculation
	float *mValue;           ///< Array storing target output values for each point
	float *mAdc;             ///< Array storing raw input values (e.g., ADC) for each point
};

#endif