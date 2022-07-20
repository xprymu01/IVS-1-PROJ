//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     MAREK PRYMUS <xprymu01@fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author MAREK PRYMUS
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree: public ::testing::Test{
protected:
	BinaryTree *empty_tree;

	virtual void SetUp(){
		empty_tree = new BinaryTree();
	}

};

class NonEmptyTree: public ::testing::Test{
protected:
	BinaryTree *non_empty_tree;

	bool isInTree(std::vector<Node_t *>& allNodes,int passedKey){
		for(int i = 0; i < allNodes.size();i++){
			if(passedKey == allNodes[i]->key){
				return true;
			}
		}
		return false;
	}
	
	virtual void SetUp(){				// vložení náhodných hodnot (max 50  do stromu o velikosti max 50
		non_empty_tree = new BinaryTree();
		for(int i = 0;i < rand()%50;i++){
			non_empty_tree->InsertNode(rand()%50);
		}
	}
};

class ThreeAxioms: public ::testing::Test{
protected:
	BinaryTree *three_axioms;

	virtual void SetUp(){				
		three_axioms = new BinaryTree();
		for(int i = 0;i < rand()%50;i++){
			three_axioms->InsertNode(rand()%50);
		}
	}
};

TEST_F(EmptyTree,InsertNode){
	std::pair<bool, Node_t *> node = empty_tree->InsertNode(1);
	ASSERT_TRUE(node.first);
	ASSERT_TRUE(node.second != NULL);
	EXPECT_EQ(NULL,node.second->pParent);
	EXPECT_EQ(1,node.second->key);
}

TEST_F(EmptyTree,DeleteNode){
	for(int i = 1;i < 100;i++){
		EXPECT_FALSE(empty_tree->DeleteNode(i));
	}
}

TEST_F(EmptyTree,FindNode){
	for(int i = 1;i < 100;i++){
		EXPECT_EQ(NULL,empty_tree->FindNode(i));
	}
}



TEST_F(NonEmptyTree,InsertNode){
	std::vector<Node_t *> allNodes ;
	non_empty_tree->GetAllNodes(allNodes);
	for(int i = 1;i < 50;i++){
		if(isInTree(allNodes,i)){
			EXPECT_FALSE(non_empty_tree->InsertNode(i).first);
		}
		else{
			EXPECT_TRUE(non_empty_tree->InsertNode(i).first);
		}
	}	
}

TEST_F(NonEmptyTree,DeleteNode){
	std::vector<Node_t *> allNodes ;
	non_empty_tree->GetAllNodes(allNodes);
	for(int i = 1;i < 50;i++){
		if(isInTree(allNodes,i)){
			EXPECT_TRUE(non_empty_tree->DeleteNode(i));
		}
		else{
			EXPECT_FALSE(non_empty_tree->DeleteNode(i));
		}
	}
}

TEST_F(NonEmptyTree,FindNode){
	std::vector<Node_t *> allNodes ;
	non_empty_tree->GetAllNodes(allNodes);
	for(int i = 1;i < 50;i++){
		if(isInTree(allNodes,i)){
			Node_t *temp = non_empty_tree->InsertNode(i).second;
			EXPECT_EQ(temp,non_empty_tree->FindNode(i));
		}
		else{
			EXPECT_EQ(NULL,non_empty_tree->FindNode(i));
		}
	}	
}




TEST_F(ThreeAxioms,Axiom1){
	std::vector<Node_t*> leafs;
	three_axioms->GetLeafNodes(leafs);
	for(int i = 0;i < leafs.size();i++){
		EXPECT_EQ(BLACK,leafs[i]->color);
	}
}

TEST_F(ThreeAxioms,Axiom2){
	std::vector<Node_t*> nodes;
	three_axioms->GetAllNodes(nodes);
	for(int i = 0;i < nodes.size() ;i++){
		if(nodes[i]->color == RED){
			EXPECT_EQ(BLACK,nodes[i]->pLeft->color);
			EXPECT_EQ(BLACK,nodes[i]->pRight->color);
		}
	}
}

TEST_F(ThreeAxioms,Axiom3){
	std::vector<Node_t*> leafs;
	three_axioms->GetLeafNodes(leafs);
	Node_t *tmp = leafs[0];
	int reference_lenght = 0;
	while(tmp != NULL){
		if(tmp->color == BLACK){
			reference_lenght ++;
		}
		tmp = tmp->pParent;
	}

	for(int i = 0;i < leafs.size();i++){
		int counter = 0;
		tmp = leafs[i];
		while(tmp != NULL){
			if(tmp->color == BLACK){
				counter ++;
			}
		tmp = tmp->pParent;
		}
		EXPECT_EQ(counter,reference_lenght);
	}

}




/*** Konec souboru black_box_tests.cpp ***/
