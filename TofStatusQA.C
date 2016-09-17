

{

	Logger::setGlobalLogLevel( "info" );

	XmlConfig c( "TofStatusQA.xml" );
	HistoBook b( "TofStatusQA.root", c );

	b.makeAll( "histograms" );
	INFO( "", "# of histograms = " << b.size() );

	TChain * tof = new TChain( "tof" );

	tof->Add( c.getString( "glob:url" ).c_str() );

	tof->Draw( "tray>>Trays" );

	b.cd("modules");
	for ( int iTray = 1; iTray < 121; iTray ++ ){
		b.clone( "", "Module", "Module_" + ts(iTray) );
		INFO( "", "Modules for Tray " << iTray );
		tof->Draw( ("module>>Module_" + ts(iTray)).c_str(), ("tray==" + ts(iTray)).c_str() );
	}

	b.cd("cells");
	for ( int iTray = 1; iTray < 121; iTray ++ ){
		for ( int iMod = 1; iMod <= 32; iMod ++ ){
			INFO( "", "Cells for Tray " << iTray << ", Module " << iMod  );
			string name = "Cell_" + ts(iTray) + "_" + ts(iMod);
			b.clone( "", "Cell", name );	
			tof->Draw( ("cell>>" + name ).c_str(), ("tray==" + ts(iTray) + " && module==" + ts(iMod) ).c_str() );
		}
	}


	b.save();

}