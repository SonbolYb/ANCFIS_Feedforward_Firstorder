/*
 * AncfisNet.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: sonbol
 */

#include "AncfisNet.h"
using namespace std;

/*******************************************************************
An object of timeSeries and inputVecWeight class are instantiate in
the constructor.
 *******************************************************************/
AncfisNet::AncfisNet():commandLine(),rinputVectorWeight(inputVectorWeight),trainMatrix(NULL){
}

/*******************************************************************
Cal_outputWeight()

Use: 	This method obtains output weights of ELM by using all the input vectors
		in the training set and through a number of epochs.

Out:	The best output weights obtained through iterations over epochs.
 	 	 The one has the lowest training error.
 	 	 The weights are used to make a network for checking data.

Status:	Public method called from main function.

PreConditions: Objects of timeSeries and inputVecWeight have been instantiated.

Postconditions:	1. If we are in the first epoch, we read the original training set
					otherwise, we shuffle the training set and use it.
				2. For each epoch, we go through all the input vectors in the training/shuffle one
					and update the weights for them.
				3. At the end of each epoch, it is checked if we reached to the threshold or the number of epoch.

Invariant:
 *******************************************************************/

std::vector<std::vector<double>>* AncfisNet::Cal_outputWeight(){
	
	int epochPass=0;
	for(int epoch=0;epoch <numEpoch;epoch++){
		if(epoch ==0 ){
			trainMatrix=training.getTraining();
		}
		else{
			trainMatrix=training.shuffleTraining();
		}

		for (int indexInV=0; indexInV<numOfInVecTraining;indexInV++){

			vector<double> & inputVec=(*trainMatrix)[indexInV]; //No Copy happens here.
			inputVectorWeight.calculateWeight(inputVec,indexInV);	//indexinV goes as iteration for membership function
			inputVectorWeight.calErrorTr(epoch);							//Epoch goes to save the error of all the epochs .Calculate error of each input vector
		}

		inputVectorWeight.calError(epoch);							//Calculate the error at the end of epoch
		//	calError_test(inputVectorWeight,epoch);
		//checkCondition();
		if ((epoch==(numEpoch-1)) || (inputVectorWeight.getAveBest() <= threshold)){
		epochPass=epoch;
			break;
		}
	}

	inputVectorWeight.saveParams(epochPass);


	return(inputVectorWeight.getWBest());
}
/******************************************************************/

