/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Tue Jul 17 16:02:29 EDT 2018 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"
#include <math.h>


/**
 * Two AND gates connected to make a 3-input AND circuit.
 
static Circuit* and3_Circuit() {
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* A1 = new_AndGate();
	Gate* A2 = new_AndGate();
	Gate** gates = new_Gate_array(2);
	gates[0] = A1;
	gates[1] = A2;

	Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 2, gates);
	Circuit_connect(circuit, x, Gate_getInput(A1, 0));
	Circuit_connect(circuit, y, Gate_getInput(A1, 1));
	Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(A2, 0));
	Circuit_connect(circuit, z, Gate_getInput(A2, 1));
	Circuit_connect(circuit, Gate_getOutput(A2), out);
	return circuit;
}
*/
static char* b2s(bool b) {
	return b ? "T" : "F";
}



/**
 * circuit a
 */
static Circuit* circuit_a() {
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* not1 = new_Inverter();
	Gate* and1 = new_AndGate();
	Gate* and2 = new_AndGate();
	Gate* or1 = new_OrGate();
	Gate** gates = new_Gate_array(4);
	gates[0] = not1;
	gates[1] = and1;
	gates[2] = and2;
	gates[3] = or1;

	Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 4, gates);
	Circuit_connect(circuit, y, Gate_getInput(not1, 0)); //inverted gate
	Circuit_connect(circuit, x, Gate_getInput(and1, 0)); //add x to add gate
	Circuit_connect(circuit, Gate_getOutput(not1),Gate_getInput(and1,1)); //add inverted y to and gate
	Circuit_connect(circuit,y ,Gate_getInput(and2,0)); //andgate 2: add y
	Circuit_connect(circuit,z, Gate_getInput(and2,1)); //andgate 2: add z
	Circuit_connect(circuit, Gate_getOutput(and1), Gate_getInput(or1, 0)); // or gate of output of andgate 1 and 2
	Circuit_connect(circuit, Gate_getOutput(and2), Gate_getInput(or1, 1)); // or gate of output of andgate 1 and 2
	Circuit_connect(circuit, Gate_getOutput(or1), out);
	return circuit;
}



/**
 * circuit b
 */
static Circuit* circuit_b() {
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* not1 = new_Inverter();
	Gate* nand1 = new_NANDGate();
	Gate* nand2 = new_NANDGate();
	Gate* nor1 = new_NORGate();;
	Gate** gates = new_Gate_array(4);
	gates[0] = not1;
	gates[1] = nand1;
	gates[2] = nand2;
	gates[3] = nor1;

	Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 4, gates);
	Circuit_connect(circuit, y, Gate_getInput(not1, 0)); //inverted gate
	Circuit_connect(circuit, x, Gate_getInput(nand1, 0)); //add x to nand gate
	Circuit_connect(circuit, Gate_getOutput(not1),Gate_getInput(nand1,1)); //add inverted y to and gate
	Circuit_connect(circuit,y ,Gate_getInput(nand2,0)); //nandgate 2: add y
	Circuit_connect(circuit,z, Gate_getInput(nand2,1)); //nandgate 2: add z
	Circuit_connect(circuit, Gate_getOutput(nand1), Gate_getInput(nor1, 0)); // nor gate of output of nandgate 1 and 2
	Circuit_connect(circuit, Gate_getOutput(nand2), Gate_getInput(nor1, 1)); // nor gate of output of nandgate 1 and 2
	Circuit_connect(circuit, Gate_getOutput(nor1), out);
	return circuit;
}



/**
 * circuit c
 */
static Circuit* circuit_c() {
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(2);
	inputs[0] = x;
	inputs[1] = y;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* not1 = new_Inverter();
	Gate* and1 = new_AndGate();
	Gate* not2 = new_Inverter();
	Gate* and2 = new_AndGate();
	Gate* or1 = new_OrGate();
	Gate** gates = new_Gate_array(5);
	gates[0] = not1;
	gates[1] = and1;
	gates[2] = not2;
	gates[3] = and2;
	gates[4] = or1;

	Circuit *circuit = new_Circuit(2, inputs, 1, outputs, 5, gates);
	Circuit_connect(circuit, x, Gate_getInput(not1, 0)); //get inverted of x
	Circuit_connect(circuit, y, Gate_getInput(not2, 0)); //get inverted of y
	Circuit_connect(circuit, Gate_getOutput(not1), Gate_getInput(and1, 0));
	Circuit_connect(circuit, Gate_getOutput(not2), Gate_getInput(and1, 1));//add both the inversions to first and
	Circuit_connect(circuit, x, Gate_getInput(and2, 0));
	Circuit_connect(circuit, y, Gate_getInput(and2, 1)); //add both real x and y vals to second and
	Circuit_connect(circuit, Gate_getOutput(and1), Gate_getInput(or1, 0));
	Circuit_connect(circuit, Gate_getOutput(and2), Gate_getInput(or1, 1)); //get results of and and add them to the or
	Circuit_connect(circuit, Gate_getOutput(or1), out);

	return circuit;
}

/**
 * circuit bitadder
 */
static Circuit* circuit_bitadder() {
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* c = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = c;

	Boolean* z = new_Boolean(false);
	Boolean* d = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(2);
	outputs[0] = z;
	outputs[1] = d;

	Gate* not1 = new_Inverter();
	Gate* not2 = new_Inverter();
	Gate* not3 = new_Inverter();
	Gate* and1 = new_And3Gate();
	Gate* and2 = new_And3Gate();
	Gate* and3 = new_And3Gate();
	Gate* and4 = new_And3Gate();
	Gate* and5 = new_And3Gate();
	Gate* and6 = new_And3Gate();
	Gate* and7 = new_And3Gate();
	Gate* or1 = new_Or4Gate();
	Gate* or2 = new_Or4Gate();
	Gate** gates = new_Gate_array(12);
	gates[0] = not1;
	gates[1] = not2;
	gates[2] = not3;
	gates[3] = and1;
	gates[4] = and2;
	gates[5] = and3;
	gates[6] = and4;
	gates[7] = and5;
	gates[8] = and6;
	gates[9] = and7;
	gates[10] = or1;
	gates[11] = or2;

	Circuit *circuit = new_Circuit(3, inputs, 2, outputs, 12, gates);
	Circuit_connect(circuit, x, Gate_getInput(not1,0));
	Circuit_connect(circuit, y, Gate_getInput(not2,0));
	Circuit_connect(circuit, c, Gate_getInput(not3,0));
	Circuit_connect(circuit, Gate_getOutput(not1), Gate_getInput(and1,0));
	Circuit_connect(circuit, Gate_getOutput(not2), Gate_getInput(and1,1));
	Circuit_connect(circuit, c, Gate_getInput(and1,2));
	Circuit_connect(circuit, Gate_getOutput(not1), Gate_getInput(and2,0));
	Circuit_connect(circuit, y, Gate_getInput(and2,1));
	Circuit_connect(circuit, Gate_getOutput(not3), Gate_getInput(and2,2));
	Circuit_connect(circuit, Gate_getOutput(not1), Gate_getInput(and3,0));
	Circuit_connect(circuit, y, Gate_getInput(and3,1));
	Circuit_connect(circuit, c, Gate_getInput(and3,2));
	Circuit_connect(circuit, x, Gate_getInput(and4,0));
	Circuit_connect(circuit, Gate_getOutput(not2), Gate_getInput(and4,1));
	Circuit_connect(circuit, Gate_getOutput(not3), Gate_getInput(and4,2));
	Circuit_connect(circuit, x, Gate_getInput(and5,0));
	Circuit_connect(circuit, Gate_getOutput(not2), Gate_getInput(and5,1));
	Circuit_connect(circuit, c, Gate_getInput(and5,2));
	Circuit_connect(circuit, x, Gate_getInput(and6,0));
	Circuit_connect(circuit, y, Gate_getInput(and6,1));
	Circuit_connect(circuit, Gate_getOutput(not3), Gate_getInput(and6,2));
	Circuit_connect(circuit, x, Gate_getInput(and7,0));
	Circuit_connect(circuit, y, Gate_getInput(and7,1));
	Circuit_connect(circuit, c, Gate_getInput(and7,2));
	Circuit_connect(circuit, Gate_getOutput(and1), Gate_getInput(or1,0));
	Circuit_connect(circuit, Gate_getOutput(and2), Gate_getInput(or1,1));
	Circuit_connect(circuit, Gate_getOutput(and4), Gate_getInput(or1,2));
	Circuit_connect(circuit, Gate_getOutput(and7), Gate_getInput(or1,3));
	Circuit_connect(circuit, Gate_getOutput(and3), Gate_getInput(or2,0));
	Circuit_connect(circuit, Gate_getOutput(and5), Gate_getInput(or2,1));
	Circuit_connect(circuit, Gate_getOutput(and6), Gate_getInput(or2,2));
	Circuit_connect(circuit, Gate_getOutput(and7), Gate_getInput(or2,3));
	Circuit_connect(circuit, Gate_getOutput(or1), z);
	Circuit_connect(circuit, Gate_getOutput(or2), d);
	return circuit;
}






static void circuit_tester(Circuit* circuit){
	int maxPossibilities = pow(2.0, Circuit_numInputs(circuit));
	printf("this is the num of maxPossibilities: %d\n", maxPossibilities);
	for(int i = 0; i < maxPossibilities; i++){ //possiblities of T/F
		int binInputs[Circuit_numInputs(circuit)];
		for(int j = 0; j < Circuit_numInputs(circuit); j++){
			binInputs[Circuit_numInputs(circuit) - j - 1] = (i >> j) & 1; //get binary representation fo input
		}
		for(int s = 0; s < Circuit_numInputs(circuit); s++){ //iterate through to set inputs for this possibility T/F
			Circuit_setInput(circuit, s, binInputs[s]);	//set input
			printf("%s ", b2s(binInputs[s]));	
		}
		printf("-> ");

		Circuit_update(circuit);
		for(int t = 0; t < Circuit_numOutputs(circuit); t++){
			printf("%s", b2s(Circuit_getOutput(circuit,t))); //print output

		}
		printf("\n");
	}
}

int main(int argc, char **argv) {
	Circuit* circuitA = circuit_a();
	printf("Testing CircuitA:\n");
	Circuit_dump(circuitA);
	printf("\n");
	circuit_tester(circuitA);

	Circuit* circuitB = circuit_b();
	printf("Testing CircuitB:\n");
	Circuit_dump(circuitB);
	printf("\n");
	circuit_tester(circuitB);

	Circuit* circuitC = circuit_c();
	printf("Testing CircuitC:\n");
	Circuit_dump(circuitC);
	printf("\n");
	circuit_tester(circuitC);

	Circuit* circuitBitAdder = circuit_bitadder();
	printf("Testing EXTRA CREDIT circuitBitAdder:\n");
	Circuit_dump(circuitBitAdder);
	printf("\n");
	circuit_tester(circuitBitAdder);


	
	
}

