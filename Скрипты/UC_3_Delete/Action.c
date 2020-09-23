Action()
{
	int flight_id_num = 0;


	web_set_sockets_option("SSL_VERSION", "TLS1.2");
	
	lr_start_transaction("UC_3_Delete");
	
	lr_start_transaction("goToSite");

	web_add_auto_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	 web_reg_find("Fail=NotFound",
		"Text=A Session ID has been created",
		LAST);
	
	web_reg_save_param("userSession",
		"LB=name=\"userSession\" value=\"",
		"RB=\"/>",
		"NotFound=ERROR",
		LAST);
	
	

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
		
	lr_end_transaction("goToSite", LR_AUTO);

	

	lr_start_transaction("login");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	lr_think_time(5);
	
		web_reg_find("Fail=NotFound",
		"Text=User password was correct",
		LAST);

	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={user}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=50", ENDITEM,
		"Name=login.y", "Value=15", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("click_itinenary");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(5);
	
		web_reg_save_param("flights_id",
		"LB=name=\"flightID\" value=\"",
		"RB=\"",
		"Ord=ALL",
		LAST);

		web_reg_find("Fail=NotFound",
		"Text=User wants the intineraries.",
		LAST);
	
	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	
	flight_id_num = atoi(lr_eval_string("{flights_id_count}"));

	lr_end_transaction("click_itinenary",LR_AUTO);

	lr_start_transaction("click_cancel");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(5);
	

		web_reg_save_param("flights_numbers",
		"LB=<b>A total of",
		"RB=scheduled flights.</font></b>",
		LAST);
	
 		web_submit_form("web_submit_form",
		ITEMDATA,
		"Name=1", "Value=on", ENDITEM,
		"Name=removeFlights.x", "Value=56", ENDITEM, 
		"Name=removeFlights.y", "Value=6", ENDITEM, 
		EXTRARES,
		"URL=http://localhost:1080/cgi-bin/itinerary.pl",
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
		LAST);
	
	if(atoi(lr_eval_string("{flights_numbers}")) > flight_id_num)
	{
		
		lr_fail_trans_with_error("itinerary not delete");

	} else {
		lr_output_message("itinerary delete");
	}
	
lr_end_transaction("click_cancel", LR_AUTO);

lr_start_transaction("click_sigin_off");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(5);
	
	web_reg_find("Fail=NotFound",
		"Text=A Session ID has been created",
		LAST);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("click_sigin_off", LR_AUTO);

lr_end_transaction("UC_3_Delete", LR_AUTO);

	return 0;
}