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
#include <sys/stat.h>

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
// 	cout<<"input file : "<<infile<<endl;

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
		
	double  bandwidth       = 0;		
	double  localoscillator = 0;		
	double  samplerate = 0;		
	double  source_ra = 0;		
	double  source_dec = 0;		
	 double frequency = 0;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 	
	fits_movabs_hdu(input, 1, NULL, &status);	
	fits_read_key(input, TSTRING, "PROJID", Project_Name, NULL, &status );
	fits_read_key(input, TSTRING, "TELESCOP", telescope, NULL, &status );
	fits_read_key(input, TSTRING, "DATE-OBS", date, NULL, &status );
	
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
	
       
	fits_read_key(input, TSTRING, "SRC_NAME", source, NULL, &status );
	fits_read_key(input, TSTRING, "FRONTEND", receiver, NULL, &status );	
	fits_read_key(input, TSTRING, "BACKEND", backend, NULL, &status );
        
        
        
 	fits_read_key(input, TDOUBLE, "OBSFREQ", &frequency, NULL, &status );
	fits_read_key(input, TDOUBLE, "OBSBW", &bandwidth, NULL, &status);
        
        localoscillator=frequency-(bandwidth/2)-100;
        
     
        
        
        // mjd_start
    	int imjd = 0;
	int smjs = 0;
 	double offs = 0;     
 	fits_read_key(input, TINT32BIT, "STT_IMJD", &imjd, NULL, &status );        
	fits_read_key(input, TINT32BIT, "STT_SMJD", &smjs, NULL, &status);   
  	fits_read_key(input, TDOUBLE, "STT_OFFS", &offs, NULL, &status );
        mjd_start = imjd + ((smjs)/86400.);
        
        
        
        char sRA[128];
        char sDEC[128];
        
// 	fits_read_key(input, TSTRING, "ScheduleName", ScheduleName, NULL, &status );		
	
	fits_read_key(input, TSTRING, "RA", sRA, NULL, &status );
	fits_read_key(input, TSTRING, "DEC",   sDEC, NULL, &status );		
        
        
        
        
        
  	strcpy(tempBuffer,sRA);
	Ptr = strtok(tempBuffer,":");
        
        double ore=atof(Ptr);
        
	Ptr = strtok(NULL,":");
         double minuti=atof(Ptr);

         Ptr = strtok(NULL,":");
         double secondi=atof(Ptr);
        
        
        source_ra=ore*15.+((minuti*15)/60.)+((secondi*15)/3600.); //+secondi/60.;
        
        
        
        
        strcpy(tempBuffer,sDEC);
	Ptr = strtok(tempBuffer,":");
        
        ore=atof(Ptr);
        
	Ptr = strtok(NULL,":");
         minuti=atof(Ptr);

         Ptr = strtok(NULL,":");
         secondi=atof(Ptr);  
        
       
         source_dec=ore+((minuti)/60.)+((secondi)/3600.); //+secondi/60.;       
        

        
        
        
        
        
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 	
	
        
        
        //smaple rate
	fits_movabs_hdu(input, 6, NULL, &status);	
        fits_read_key(input, TDOUBLE, "TBIN", &samplerate, NULL, &status );
        
        
        
        //mjdstop
        int nblsk = 0;        
 	fits_read_key(input, TINT32BIT, "NSBLK", &nblsk, NULL, &status); 
        mjd_stop = mjd_start +(nblsk*samplerate)/86400.;      

//         printf("%f - %f \n",mjd_start,mjd_stop);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 	

        float filesize = 0; 
        struct stat st; 

        if (stat(infile, &st) == 0)
            filesize = ((st.st_size/1024./1024.)* 10.0)/10.0;   			
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 	

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
		
		

	
		sprintf(express,"INSERT IGNORE INTO %s (filename, date, source, Project_Name, telescope, mjd_start, mjd_stop, frequency, bandwidth, localoscillator, samplerate, receiver, backend, project_dir, ScheduleName, source_ra, source_dec, size) VALUES ('%s', '%s', '%s',  '%s', '%s', %f, %f, %f, %f, %f, %f,'%s', '%s', '%s', '%s', %f, %f, %f)",table, infile, date, source, Project_Name, telescope, mjd_start, mjd_stop, frequency, bandwidth, localoscillator, samplerate, receiver, backend, project_dir, ScheduleName, source_ra, source_dec, filesize);	                
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