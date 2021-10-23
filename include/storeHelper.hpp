#ifndef STORE_HELPER_HPP
#define STORE_HELPER_HPP

auto store=[]{
	vmime::utility::url url(*urlStringimap);
	vmime::shared_ptr<vmime::net::store> st;
	st=g_session->getStore(url);
	
	st->setProperty("connection.tls",true);
	st->setProperty("auth.username", *username);
	st->setProperty("auth.password", *password);
	st->setProperty("options.need-authentication", "true");
	st->setCertificateVerifier(vmime::make_shared <interactiveCertificateVerifier>());
	st->connect();

	vmime::shared_ptr <vmime::net::connectionInfos> ci = st->getConnectionInfos();
	auto a=ci->getHost();
	auto b=ci->getPort();
	
	line.clear();	//uncomment this, if want to render multiple messages on same screen
	line.push_back(text("Inbox Status: ")|color(Color::Blue));
	line.push_back(text("Connected to   URL: " +a+ "    PORT: " + std::to_string(b)) | color(Color::Green));

	vmime::shared_ptr <vmime::net::folder> f = st->getDefaultFolder();
	f->open(vmime::net::folder::MODE_READ_WRITE);
	vmime::size_t count = f->getMessageCount();
	line.push_back(text(std::to_string(count)+" message(s) in your inbox"));
	
	typedef std::map <vmime::size_t, vmime::shared_ptr <vmime::net::message> > MessageList;
	MessageList msgList;
	vmime::shared_ptr <vmime::net::message> msg;
	msg = f->getMessage(std::stoi(num));
	msgList.insert(MessageList::value_type(std::stoi(num), msg));

	vmime::net::fetchAttributes attr(vmime::net::fetchAttributes::ENVELOPE);
	f->fetchMessage(msg, attr);
	auto outputDate    = msg->getHeader()-> Date()->   generate();
	auto outputSubject = msg->getHeader()-> Subject()->generate();
	auto outputFrom    = msg->getHeader()-> From()->   generate();
	auto outputTo      = msg->getHeader()-> To()->     generate();
	auto outputSender  = msg->getHeader()-> Sender()-> generate();

	vmime::net::fetchAttributes attr1(vmime::net::fetchAttributes::STRUCTURE);
	f->fetchMessage(msg, attr1);
	
	vmime::utility::outputStreamStringAdapter outStr(bodyStr);
	msg->extractPart(msg->getStructure()->getPartAt(0),outStr);

	line.push_back(text(" "));
	line.push_back(text("Message "+num+":"));
	line.push_back(text(outputDate)   | flex);
	line.push_back(text(outputSubject)| flex);
	line.push_back(text(outputFrom)   | flex);
	line.push_back(text(outputTo)     | flex);
	line.push_back(text(outputSender) | flex);
	//line.push_back(text(bodyStr));        comment out, to print body of the message

	st->disconnect();
	return line;
};


#endif