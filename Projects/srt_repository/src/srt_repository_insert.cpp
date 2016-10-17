/* Copyright 2008, 2010, Oracle and/or its affiliates. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

There are special exceptions to the terms and conditions of the GPL
as it is applied to this software. View the full text of the
exception in file EXCEPTIONS-CONNECTOR-C++ in the directory of this
software distribution.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/


// g++ -o test   -lmysqlcppconn example.cpp


#include "srt_repository_insert.h"


/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#define DEG2RAD 0.017453292519943295769
#define RAD2DEG 57.295779513082320877

using namespace std;

int main(int argc,char **argv) {

  
  
	char express[1024];
	char express2[1024];
	char express3[1024];
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // d
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

	int status = 0;
	fitsfile *input;
	char * db = argv[1];	
	char table[7];
	char * infile = argv[2];
	
	
	
// 	char * project_dir = argv[4];	
	
	fits_open_file(&input, infile, READONLY, &status);
	if ( status) {
                fits_report_error(stderr, status);
		return status;
		}	
	//cout<<"input file : "<<infile<<endl;

	long nrows  = 0;
	int colnum = 0;
	char keyword[128];
	long nchannels = 0;	
	double fractpart, intpart;	
	double  mjd_start = 0;
	double  mjd_stop = 0;
	
	char Project_Name[128];	
	char project_dir[128];	
	char date[128];	
	char tempBuffer[1024];		
	char source[128];		
	char telescope[128];	
	char receiver[128];		
	char backend[128];	
	char ScheduleName[255];
	double  frequency       = 0;	
	double  bandwidth       = 0;		
	double  localoscillator = 0;		
	double  samplerate = 0;		
	double  source_ra = 0;		
	double  source_dec = 0;		
	
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 	
	fits_movabs_hdu(input, 1, NULL, &status);	
	fits_read_key(input, TSTRING, "Project_Name", Project_Name, NULL, &status );
	fits_read_key(input, TSTRING, "ANTENNA", telescope, NULL, &status );
	fits_read_key(input, TSTRING, "DATE", date, NULL, &status );
	

	char *Ptr;
	char year[4];
	char month[2];
	char day[2];
	strcpy(tempBuffer,date);
	Ptr = strtok(tempBuffer,"-");	
	strcpy(year, Ptr);
	Ptr = strtok(NULL,"-");
	strcpy(month, Ptr);
	Ptr = strtok(NULL,"-T");
	strcpy(day, Ptr);
	
	
	strcpy(tempBuffer,infile);
	Ptr = strtok(tempBuffer,"/");
	
	

	int indexB = 0;
	
	while(Ptr != NULL) {
		indexB++;
		Ptr = strtok(NULL,"/");
		}
	
	strcpy(tempBuffer,infile);
	Ptr = strtok(tempBuffer,"/");	
	
	int k = 0;
	while((k <  indexB-2) && (Ptr != NULL)) {
		Ptr = strtok(NULL,"/");
		k++;
		}	
// 	cout<<Ptr<<endl;
	strcpy(project_dir,Ptr);
	sprintf(table,"%s",argv[3]);
	
// 	cout<<table<<endl;
// 	cout<<table<<endl;
// 	cout<<table<<endl;
	
	fits_read_key(input, TSTRING, "SOURCE", source, NULL, &status );
	fits_read_key(input, TSTRING, "Receiver Code", receiver, NULL, &status );	
	fits_read_key(input, TSTRING, "Backend Name", backend, NULL, &status );
	if (status !=0) {
		sprintf(backend,"TP");
		status = 0;
		}
	fits_read_key(input, TSTRING, "ScheduleName", ScheduleName, NULL, &status );		
	
	fits_read_key(input, TDOUBLE, "RightAscension", &source_ra, NULL, &status );
	fits_read_key(input, TDOUBLE, "Declination",   &source_dec, NULL, &status );		
	source_ra  = source_ra*RAD2DEG; 
	source_dec = source_dec*RAD2DEG;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 	
	
	
	fits_movabs_hdu(input, 2, NULL, &status);	
	fits_get_num_rows(input,  &nchannels,  &status);	

	fits_get_colnum(input, 1, "sampleRate", &colnum, &status);	
	fits_read_col(input, TDOUBLE, colnum, 1, 1, 1, NULL, &samplerate, NULL, &status);	

	samplerate = 1./(samplerate*1000.);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 	
	
	
	fits_movabs_hdu(input, 3, NULL, &status);	

	fits_get_colnum(input, 1, "frequency", &colnum, &status);	
	fits_read_col(input, TDOUBLE, colnum, 1, 1, 1, NULL, &frequency, NULL, &status);		

	

	fits_get_colnum(input, 1, "bandWidthRoach2", &colnum, &status);
			
	if (status == 219) {
		cout<<"stai usando una vecchia versione di file roach2 (bandWidthRoach2 non esiste) ed useremo bandWidth TP"<<endl;
		status = 0; 
		fits_get_colnum(input, 1, "bandWidth", &colnum, &status);	
		}	
	
	fits_get_colnum(input, 1, "bandWidth", &colnum, &status);	
	fits_read_col(input, TDOUBLE, colnum, 1, 1, 1, NULL, &bandwidth, NULL, &status);

	

	
	fits_get_colnum(input, 1, "localOscillator", &colnum, &status);	
	fits_read_col(input, TDOUBLE, colnum, 1, 1, 1, NULL, &localoscillator, NULL, &status);	
	
// 	frequency=localoscillator+bandwidth/2.;	
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 	
	
	fits_movabs_hdu(input, 5, NULL, &status);		
	fits_get_num_rows(input,  &nrows,  &status);
	
	fits_get_colnum(input, 1, "time", &colnum, &status);	
	fits_read_col(input, TDOUBLE, colnum, 1, 1, 1, NULL, &mjd_start, NULL, &status);	
	fits_read_col(input, TDOUBLE, colnum, nrows, 1, 1, NULL, &mjd_stop, NULL, &status);	
	
// 	printf("%f-%f\n",mjd_stop,mjd_start);
// 	cout<<nrows<<endl;

	if ((mjd_stop-mjd_start)!=0)
		samplerate = nrows*1./((mjd_stop-mjd_start)*86400.);
	else
		samplerate = 0;
	
	fits_close_file(input, &status);	

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
			
			

	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;		
			
		sql::ResultSet *res;

		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect("tcp://localhost:3306", "fitswriter", "7GMSwRsSyajXLupN");
		
		
		stmt = con->createStatement();
		
		sprintf(express,"USE  %s",db);	
		stmt->execute(express);
		
		
		

		
// 		cout<<express<<endl;
		stmt->execute(express);
		

		sprintf(express,"INSERT IGNORE INTO %s (filename, date, source, Project_Name, telescope, mjd_start, mjd_stop, frequency, bandwidth, localoscillator, samplerate, receiver, backend, project_dir, ScheduleName, source_ra, source_dec) VALUES ('%s', '%s', '%s',  '%s', '%s', %f, %f, %f, %f, %f, %f,'%s', '%s', '%s', '%s', %f, %f)",table, infile, date, source, Project_Name, telescope, mjd_start, mjd_stop, frequency, bandwidth, localoscillator, samplerate, receiver, backend, project_dir, ScheduleName, source_ra, source_dec);	
		//cout<<express<<endl;
		stmt->execute(express);

		

		
		
		delete stmt;
		delete con;	
			

	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line "  << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	
        if (status) {
                fits_report_error(stderr, status);
                }
        else {	
                printf("STATUS %d\n",status);
                }
	return EXIT_SUCCESS;
}
