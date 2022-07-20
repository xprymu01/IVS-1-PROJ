//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     MAREK PRYMUS <xprymu01@vutbr.cz>
// $Date:       $2021-01-03
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author MAREK PRYMUS
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class MatrixTesting : public ::testing::Test{
protected:
	Matrix *matrix;
	Matrix *testmatrix1;
	Matrix *testmatrix2;
	Matrix *testmatrix3;

	virtual void SetUp(){
		matrix = new Matrix();
		testmatrix1 = new Matrix(2,2);
		testmatrix2 = new Matrix(2,2);
		testmatrix3 = new Matrix(3,3);

		testmatrix1->set(std::vector<std::vector<double>> {
				{1, 2},
				{3, 4},
		});

		testmatrix2->set(std::vector<std::vector<double>> {
				{10, 20},
				{30, 40},
		});

		testmatrix3->set(std::vector<std::vector<double>> {
				{5, 6, 8},
				{3, 16, 4},
				{1, 1, 1},
		});
	}

	virtual void TearDown(){
		delete matrix;
		delete testmatrix1;
		delete testmatrix2;
		delete testmatrix3;
	}
};


TEST_F(MatrixTesting,Constructor){
	EXPECT_NO_THROW(Matrix());

	for(int i = 0;i < 5;i++){
		EXPECT_NO_THROW(Matrix(rand()%250+1,rand()%250+1));
	}
	EXPECT_ANY_THROW(Matrix(0,1));
	EXPECT_ANY_THROW(Matrix(1,0));
	EXPECT_ANY_THROW(Matrix(0,0));
}

TEST_F(MatrixTesting,SetScalar){
	Matrix scalarTest2x2(2,2);

	EXPECT_TRUE(scalarTest2x2.set(0,0,1));
	EXPECT_TRUE(scalarTest2x2.set(1,1,55));
	EXPECT_FALSE(scalarTest2x2.set(-1,0,10));
	EXPECT_FALSE(scalarTest2x2.set(2,2,128));

	Matrix scalarTest3x2(3,2);
	EXPECT_TRUE(scalarTest3x2.set(0,0,5));
	EXPECT_TRUE(scalarTest3x2.set(2,1,65));
	EXPECT_FALSE(scalarTest3x2.set(3,0,15));
	EXPECT_FALSE(scalarTest3x2.set(2,2,128));

}

TEST_F(MatrixTesting,SetVector){
	Matrix vectorTest(2,2);
	Matrix badMatrix(1,1);
	std::vector<std::vector<double>> setTest = {
			{1, 2},
			{3, 4},
	};

	EXPECT_TRUE(vectorTest.set(setTest));
	EXPECT_FALSE(badMatrix.set(setTest));

	std::vector<std::vector<double>> setError = {
			{1, 2, 3},
			{4, 5, 6},
	};

	EXPECT_FALSE(vectorTest.set(setError));
}

TEST_F(MatrixTesting,Get){
	Matrix getTest(2,2);
	getTest.set(0,0,64);
	getTest.set(1,1,32);

	EXPECT_EQ(getTest.get(1,1),32);
	EXPECT_EQ(getTest.get(0,0),64);
	EXPECT_ANY_THROW(getTest.get(0,-1));
	EXPECT_ANY_THROW(getTest.get(0,2));
}

TEST_F(MatrixTesting,MatrixEquality){
	Matrix eqTest1(2,2);
	Matrix eqTest2(2,2);
	Matrix eqTest3(3,2);

	EXPECT_TRUE(eqTest1 == eqTest2);
	EXPECT_TRUE(eqTest1 == eqTest1);


	EXPECT_ANY_THROW(eqTest1 == eqTest3);
	EXPECT_ANY_THROW(eqTest2 == eqTest3);

	eqTest1.set(0,0,1);

	EXPECT_FALSE(eqTest1 == eqTest2);

}

TEST_F(MatrixTesting,MatrixAddition){
	
	EXPECT_ANY_THROW(*testmatrix1+*testmatrix3);
	EXPECT_ANY_THROW(*testmatrix1+*matrix);
	Matrix resultT1T2 = *testmatrix1 + *testmatrix2 ;
	Matrix resultT3T3 = *testmatrix3 + *testmatrix3 ;


	Matrix expectedT1T2(2,2);
	Matrix expectedT3T3(3,3);
	expectedT1T2.set(std::vector<std::vector<double>> {
			{11, 22},
			{33, 44},
	});
	expectedT3T3.set(std::vector<std::vector<double>> {
			{10, 12, 16},
			{6, 32, 8},
			{2, 2, 2},
	});

	EXPECT_TRUE(expectedT1T2 == resultT1T2);
	EXPECT_TRUE(expectedT3T3 == resultT3T3);

}

TEST_F(MatrixTesting,MatrixMultiplication){

	Matrix resultT1T2 = *testmatrix1 * *testmatrix2;
	Matrix expectedT1T2(2,2);

	expectedT1T2.set(std::vector<std::vector<double>> {
			{70, 100},
			{150, 220},
	});

	Matrix resultT3T3 = *testmatrix3 * *testmatrix3;
	Matrix expectedT3T3(3,3);
	expectedT3T3.set(std::vector<std::vector<double>> {
			{51, 134, 72},
			{67, 278, 92},
			{9, 23, 13},
	});

	EXPECT_TRUE(expectedT1T2 == resultT1T2);
	EXPECT_TRUE(expectedT3T3 == resultT3T3);

	EXPECT_ANY_THROW(*matrix * *testmatrix1);
	EXPECT_ANY_THROW(*testmatrix3* *testmatrix1);
}

TEST_F(MatrixTesting,MatrixMultiplication_Scalar){
	Matrix expectedZero = *matrix * 66;
	EXPECT_EQ(expectedZero,*matrix);
	expectedZero = *testmatrix1 * 0;
	EXPECT_EQ(expectedZero,Matrix(2,2));
	Matrix result = *testmatrix1  * 2;
	Matrix expected(2,2);
	expected.set(std::vector<std::vector<double>> {
			{2, 4},
			{6, 8},
	});
	EXPECT_EQ(expected,result);

}

TEST_F(MatrixTesting,SolveEquation){
	std::vector<double> expected = {-6,7};
	std::vector<double> params = {8,10};
	EXPECT_EQ(expected,testmatrix1->solveEquation(params));
	Matrix matrix1(1,1);
	matrix1.set(0,0,1);
	std::vector<double> params1 = {8};
	EXPECT_NO_THROW(matrix1.solveEquation(params1));
	std::vector<double> expectedT3 = {0,0,0};
	std::vector<double> paramsT3 = {0,0,0};
	EXPECT_EQ(expectedT3,testmatrix3->solveEquation(paramsT3));

	EXPECT_ANY_THROW(testmatrix1->solveEquation(paramsT3));
	EXPECT_ANY_THROW(testmatrix3->solveEquation(params));
	Matrix notSquareMatrix = Matrix(3,2);
	EXPECT_ANY_THROW(notSquareMatrix.solveEquation(params));

	Matrix singular(2,2);
	singular.set(std::vector<std::vector<double>> {
			{1, 1},
			{0, 0},
	});
	EXPECT_ANY_THROW(singular.solveEquation(params));	

	Matrix matrix4(4,4);
	matrix4.set(std::vector<std::vector<double>> {
			{0, 1, 5, -1},
			{5, 0, -2, 2},
			{-1, 2, -3, 1},
			{3, 0, 1, 2}
	});
	std::vector<double> params4 = {-6,8,3,-2};
	std::vector<double> expected4 = {2,1,-2,-3};
	EXPECT_EQ(matrix4.solveEquation(params4),expected4);

}

TEST_F(MatrixTesting,Transpose){
	Matrix transposeT1 = testmatrix1->transpose();


	Matrix expectedT1(2,2);
	expectedT1.set(std::vector<std::vector<double>> {
			{1, 3},
			{2, 4},
	});

	EXPECT_TRUE(transposeT1 == expectedT1);
	EXPECT_TRUE(*testmatrix1 == transposeT1.transpose());	

}

TEST_F(MatrixTesting,Inverse){
	Matrix badMatrix(2,3);
	Matrix badMatrix2(3,2);

	EXPECT_ANY_THROW(badMatrix.inverse());
	EXPECT_ANY_THROW(badMatrix2.inverse());
	EXPECT_ANY_THROW(matrix->inverse());

	Matrix inverseT1 = testmatrix1->inverse();
	Matrix expectedT1(2,2);
	expectedT1.set(std::vector<std::vector<double>> {
			{1, 0},
			{0, 1},
	});
	EXPECT_EQ(expectedT1,*testmatrix1 * inverseT1); 
	Matrix singular(2,2);
	singular.set(std::vector<std::vector<double>> {
			{1, 1},
			{0, 0},
	});
	EXPECT_ANY_THROW(singular.inverse());	

	Matrix matrix3(3,3);
	matrix3.set(std::vector<std::vector<double>> {
			{3, 3, -1},
			{-2, -2, 1},
			{-4, -5, 2}
	});

	Matrix expected3(3,3);
	expected3.set(std::vector<std::vector<double>> {
			{1, -1, 1},
			{0, 2, -1},
			{2, 3, 0}
	});

	EXPECT_EQ(expected3,matrix3.inverse());
}
/*** Konec souboru white_box_tests.cpp ***/
