

{

	TTimeStamp timestamp;
	cout << timestamp.AsString( "s" ) << endl;

	int entries = 0;

	TFile * f = new TFile( "TofStatusQA.root" );

	vector<bool> tray_status;
	tray_status.push_back( false ); // index starts at 1
	map< string, bool> module_status;


	TH1* Trays = (TH1*)f->Get( "Trays" ); 


	for ( int i = 1; i < 121; i++ ){
		if ( 1 >= Trays->GetBinContent( i+1 ) ){
			cout << i << " 0 0" << endl;
			tray_status.push_back( false );
			entries++;
		} else {
			tray_status.push_back( true );
		}
	}


	for ( int i = 1; i < 121; i++ ){
		TH1 * modules = (TH1*)f->Get( ("modules/Module_" + ts(i)).c_str() );
		if ( nullptr == modules ) continue;
		if ( false == tray_status[ i ]  ) continue;

		for ( int j = 1; j <= 32; j++ ){
			if ( 1 >= modules->GetBinContent( j+1 ) ){
				cout << i << " " << j << " 0" << endl;
				module_status[ ts(i) + "_" + ts(j) ] = false;
				entries ++;
			} else {
				module_status[ ts(i) + "_" + ts(j) ] = true;
			}
		}
	}


	for ( int i = 1; i < 121; i++ ){
		if ( false == tray_status[ i ]  ) continue;

		for ( int j = 1; j <= 32; j++ ){
			
			TH1 * cells = (TH1*)f->Get( ("cells/Cell_" + ts(i) + "_" + ts(j) ).c_str() );
			if ( nullptr == cells ) continue;
			if ( false == module_status[ ts(i) + "_" + ts(j) ] ) continue;

			for ( int k = 1; k <= 6; k++ ){
				if ( 1 >= cells->GetBinContent( k ) ){
					cout << i << " " << j << " " << k << endl;	
					entries++;
				}
			} // loop cells 
		} // loop modules
	} // loop trays

	cout << "Entries (PUT AFTER TIMESTAMP) = " << entries << endl;

}