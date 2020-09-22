Action()
{
	


	web_set_sockets_option("SSL_VERSION", "TLS1.2");
	lr_start_transaction("UC_1_Veiw_Itinerary");
	
	lr_start_transaction("goToSite");

		/*Possible OAUTH authorization was detected. It is recommended to correlate the authorization parameters.*/
	
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
	
	
		lr_think_time(5);
		

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
			"Snapshot=t8.inf", 
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
		"Snapshot=t9.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={user}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=75", ENDITEM,
		"Name=login.y", "Value=15", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("login", LR_AUTO);
	
	lr_start_transaction("click_itinenary");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(5);

	web_reg_find("Fail=NotFound",
		"Text=User wants the intineraries.",
		LAST);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("click_itinenary",LR_AUTO);

	lr_start_transaction("logout");

	
	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");
	lr_think_time(5);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		LAST);
	
lr_end_transaction("logout", LR_AUTO);

lr_end_transaction("UC_1_Veiw_Itinerary", LR_AUTO);

	
	return 0;
}