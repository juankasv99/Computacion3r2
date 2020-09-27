// CTrackAsserts.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Graph.h"
using namespace std;

// =============================================================================
// IDENTIFICACION DE LOS ALUMNOS ===============================================
// =============================================================================

const char* NombreAlumno = "nombre del alumno";
const char* ApellidosAlumno = "apellidos del alumno";
const char* NIUAlumne = "0000000"; // NIA alumno



bool CheckNIU(const char* nia)
{
	ifstream nius("Alumnes.csv");
	if (!nius.good()) {
		cout << "Error opening file Alumnes.csv" << endl;
		return false;
	}
	char buf[256];
	while (!nius.eof()) {
		nius.getline(buf, 256);
		if (buf[0] == '\0') break;
		if (strncmp(NIUAlumne, buf, 7) == 0) return true;
	}
	return false;
}

int main()
{
	cout << "PROBLEMA ASSERTS CTRACK:" << endl;
	cout << NombreAlumno << endl;
	cout << ApellidosAlumno << endl;
	cout << NIUAlumne << endl;
	if (!CheckNIU(NIUAlumne)) {
		cout << " NIU ERRONI!!!";
		return 1;
	}
	cout << endl;

	CGraph graph(false);

	graph.NewVertex("A", 1, 1);
	graph.NewVertex("B", 2, 2);
	graph.NewVertex("C", 3, 3);
	graph.NewVertex("C", 4, 4);
	graph.NewVertex("D", 5, 5);
	graph.NewVertex("E", 6, 6);
	graph.NewVertex("F", 7, 7);


	graph.NewEdge("AD",0,"A","D");
	graph.NewEdge("BD", 0, "B", "D");
	graph.NewEdge("CD", 0, "C", "D");

	graph.NewEdge("AB", 0, "A", "B");
	graph.NewEdge("BC", 0, "B","C");
	graph.NewEdge("CD", 0, "C", "D");

	graph.NewEdge("AE", 0, "A", "E");
	graph.NewEdge("BE", 0, "B", "E");
	graph.NewEdge("CE", 0, "C", "E");

	graph.NewEdge("AF", 0,"A","F");
	graph.NewEdge("BF", 0, "B", "F");
	graph.NewEdge("CF", 0, "C", "F");

	// AddFirst ----------------------------------------------------------------
	try {
		cout << "TEST NOK 01" << endl;
		CTrack track(&graph);
		track.AddFirst(NULL);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 02" << endl;
		CTrack track(NULL);
		track.AddFirst(graph.FindEdge("AD"));
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST OK 03" << endl;
		CTrack track(&graph);
		track.AddFirst(graph.FindEdge("AD"));
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 04" << endl;
		CTrack track(&graph);
		CEdge* pEdge = new CEdge("OUT",0,graph.FindVertex("A"), graph.FindVertex("B"),NULL);
		track.AddFirst(pEdge);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 05" << endl;
		CTrack track(&graph);
		cout << "SUBTEST 05.1 OK" << endl;
		track.AddFirst(graph.FindEdge("AD"));
		cout << "SUBTEST 05.2 NOK" << endl;
		track.AddFirst(graph.FindEdge("BC"));
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	// AddLast --------------------------------------------------------------------
	try {
		cout << "TEST NOK 06" << endl;
		CTrack track(&graph);
		track.AddLast(NULL);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 07" << endl;
		CTrack track(NULL);
		track.AddLast(graph.FindEdge("AD"));
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST OK 08" << endl;
		CTrack track(&graph);
		track.AddLast(graph.FindEdge("AD"));
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 09" << endl;
		CTrack track(&graph);
		CEdge* pEdge = new CEdge("OUT", 0, graph.FindVertex("A"), graph.FindVertex("B"), NULL);
		track.AddLast(pEdge);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 10" << endl;
		CTrack track(&graph);
		cout << "SUBTEST 10.1 OK" << endl;
		track.AddLast(graph.FindEdge("AD"));
		cout << "SUBTEST 10.2 NOK" << endl;
		track.AddLast(graph.FindEdge("BC"));
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	// AppendBefore ------------------------------------------------------------
	try {
		cout << "TEST NOK 11" << endl;
		CTrack track1(NULL);
		CTrack track2(&graph);
		track1.AppendBefore(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 12" << endl;
		CTrack track1(&graph);
		CTrack track2(NULL);
		track1.AppendBefore(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 13" << endl;
		CTrack track1(&graph);
		CGraph graph2(false);
		CTrack track2(&graph2);
		track1.AppendBefore(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST OK 14" << endl;
		CTrack track1(&graph);
		CTrack track2(&graph);
		cout << "SUBTEST OK 14.1" << endl;
		track2.AddLast(graph.FindEdge("BF"));
		cout << "SUBTEST OK 14.2" << endl;
		track1.AppendBefore(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST OK 15" << endl;
		CTrack track1(&graph);
		CTrack track2(&graph);
		cout << "SUBTEST OK 15.1" << endl;
		track1.AddLast(graph.FindEdge("AB"));
		cout << "SUBTEST OK 15.2" << endl;
		track1.AppendBefore(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST OK 16" << endl;
		CTrack track1(&graph);
		CTrack track2(&graph);
		cout << "SUBTEST OK 16.1" << endl;
		track1.AddLast(graph.FindEdge("AB"));
		cout << "SUBTEST OK 16.2" << endl;
		track2.AddLast(graph.FindEdge("BF"));
		cout << "SUBTEST OK 16.3" << endl;
		track2.AppendBefore(track1);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 17" << endl;
		CTrack track1(&graph);
		CTrack track2(&graph);
		cout << "SUBTEST OK 17.1" << endl;
		track1.AddLast(graph.FindEdge("AB"));
		cout << "SUBTEST OK 17.2" << endl;
		track2.AddLast(graph.FindEdge("CD"));
		cout << "SUBTEST NOK 17.3" << endl;
		track1.AppendBefore(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	// Append ---------------------------------------------------------------------
	try {
		cout << "TEST NOK 18" << endl;
		CTrack track1(NULL);
		CTrack track2(&graph);
		track1.Append(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 19" << endl;
		CTrack track1(&graph);
		CTrack track2(NULL);
		track1.Append(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 20" << endl;
		CTrack track1(&graph);
		CGraph graph2(false);
		CTrack track2(&graph2);
		track1.Append(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST OK 21" << endl;
		CTrack track1(&graph);
		CTrack track2(&graph);
		cout << "SUBTEST OK 21.1" << endl;
		track2.AddLast(graph.FindEdge("BF"));
		cout << "SUBTEST OK 21.2" << endl;
		track1.Append(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST OK 22" << endl;
		CTrack track1(&graph);
		CTrack track2(&graph);
		cout << "SUBTEST OK 22.1" << endl;
		track1.AddLast(graph.FindEdge("AB"));
		cout << "SUBTEST OK 22.2" << endl;
		track1.Append(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST OK 23" << endl;
		CTrack track1(&graph);
		CTrack track2(&graph);
		cout << "SUBTEST OK 23.1" << endl;
		track1.AddLast(graph.FindEdge("BF"));
		cout << "SUBTEST OK 23.2" << endl;
		track2.AddLast(graph.FindEdge("AB"));
		cout << "SUBTEST OK 23.3" << endl;
		track2.Append(track1);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "TEST NOK 24" << endl;
		CTrack track1(&graph);
		CTrack track2(&graph);
		cout << "SUBTEST OK 24.1" << endl;
		track1.AddLast(graph.FindEdge("AB"));
		cout << "SUBTEST OK 24.2" << endl;
		track2.AddLast(graph.FindEdge("CD"));
		cout << "SUBTEST NOK 24.3" << endl;
		track1.Append(track2);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}





}