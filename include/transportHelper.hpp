#ifndef TRANS_HELPER_HPP
#define TRANS_HELPER_HPP


//Transport service(sending mail)
auto trans=[]{
	vmime::utility::url url(*urlStringsmtp);
	vmime::shared_ptr<vmime::net::transport> tr;
	tr=g_session->getTransport(url);
	tr->setProperty("connection.tls",true);
	tr->setProperty("auth.username", *username);
	tr->setProperty("auth.password", *password);
	tr->setProperty("options.need-authentication", "true");
	tr->setCertificateVerifier(vmime::make_shared <interactiveCertificateVerifier>());
	tr->connect();
	
	data<<lines;
	vmime::string msgData = data.str();
	vmime::mailbox from(sender);
	vmime::mailboxList to;
	to.appendMailbox(vmime::make_shared <vmime::mailbox>(receiver));
	vmime::utility::inputStreamStringAdapter vis(msgData);
	if(sender==""||receiver==""||msgData=="")
	{
		line.clear();
		line.push_back(text("One/more field missing")|color(Color::Red)|blink);
	}
	else
	{
		tr->send(from,to,vis,msgData.length());
		line.clear();
		line.push_back(text("Mail Sent :)")|color(Color::Green));
		tr->disconnect();

		data.clear();lines="";sender="";receiver="";
	}
	return line;
};

#endif