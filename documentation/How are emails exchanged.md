# How are emails exchanged-
 
Exchanging emails can be divided into two sub parts –
 
1) Sending emails
2) Receiving emails
 
#### First let’s look into the sending part
 
### How are emails sent

The process of sending emails is done by a protocol called Simple Mail Transfer Protocol or SMTP in short. 

SMTP is basically a set of commands and guidelines which authenticates the transfer of email over the internet. SMTP essentially acts as a mailman who takes mail from the local post box and sends it over to the post office.

Now for different email clients, there are different SMTP server addresses -
- For Gmail it is smtp.gmail.com
- For Yahoo it is smtp.mail.yahoo.com
- For Outlook it is smtp.office365.com

This server address tells the SMTP which mail server is supposed to receive the email.

SMTP is a pure text based protocol. This means that we can send only messages that contain only text (or 7 bit ASCII). It cannot be used for images, videos, executable files or binary files. Hence to counteract these limitations an extension is used, called _Multipurpose Internet Email Extension (MIME)_. It can be used for transferring media which was not possible using plain SMTP.

So in summary, SMTP transfers the email from the sender’s local device to the sender’s mail server which varies according to the client used. Then it again transfers it to the receiver’s mail server (which also varies according to the client) over the internet. Now the task of sending the email to the local device of the receiver is done by different protocols discussed in the next section.

---



### How are emails received

Retrieving email is tasked by a software program called a _Mail User Agent (MUA)_. There are two types of MUA, and these are classed depending on how emails are accessed, via installed software **(email client)** or through browser **(webmail)**.

When an MUA is installed on a user’s system, it’s called an email client. To use an email client, MUA such as _Microsoft Outlook, Mozilla Thunderbird, and Lotus Notes_ allows users to add the MUA program to their computer. This program is used to download and store email messages to their computers. With a client MUA, emails can be read and written offline.
When email is accessed online, it’s called webmail. Web-based MUAs such as _Yahoo, Gmail, and Hotmail_ store messages on their mail servers and can only be accessed through a web page. The main advantage of webmail is sending and receiving mail from a web browser, anywhere. The main disadvantage of using a web-based application is the need to be connected to the internet to use it.

YES, Gmail and Microsoft Outlook aren’t the same my friend :)



As we had seen, SMTP was used for sending the mail, similarly a different set of protocols are used for receiving the same, viz __"POP3"__ and __"IMAP"__.

If we use _POP3(Post Office Protocol)_, then the whole email will be downloaded to the local computer and the copy at the server gets deleted. Just like its funny acronym, it's a very old protocol and not that great. It only knows how to download stuff from server to client, that’s it.

If the protocol used is _IMAP(Internet Message Access Protocol)_, then the email message is stored in the mail server itself, but the user can easily manipulate the emails on the mail server as in the local computer. This is the difference when using both the protocols and this is how your email gets delivered. If some error occurred to send the email, the emails will be delayed. There is a mail queue in every mail server. These mails will be pending in the mail queue. The mail server will keep trying to resend the email. Once the email sending failed permanently, the mail server may send a bounce back email message to the sender’s email address

IMAP is a bit smarter about things. While POP can be considered to be very “client-oriented,” the Internet Message Access Protocol was designed to work in a different way: it’s “server-oriented,” and bi-directional. All messages are kept on the server so multiple clients can access them, simultaneously. Basically, you can view the mail on every device you are logged into, as many times you want.  When you check an email on your phone, it’s marked as read and during the next interaction with the server, that status is sent back so all other clients can be updated with it. It’s like having your mail sent to an assistant at the post office who categorizes it and stores it for you, gives it to you whether you’re at home, at work, or actually there, and makes changes to the stored copies as you do.

Basically, if you want to receive mail only on one primary device, it's better to use POP. But if you have multiple devices, then go for IMAP.


This was all about the protocol of receiving emails, let’s see the basic working/pathway.
How would an envelope be delivered to the recipient on the front of the envelope? The postal service finds the most logical route to the recipient.
The electronic version of events is handled similarly:

1. The mail server locates the recipient’s server, but since the recipient’s server won’t accept every mail that comes its way, it asks who sent the email.
1. The sending server gives the recipient server information on who the sender is by querying the envelope. Acknowledging the email is from a legitimate source (not spam, etc.), the recipient server says, "sure, I understand that Namecheap exists, and from that sending address.”
1. Satisfied the sender address is correct, the recipient server asks for the receiver’. This is how envelope data is treated. The sending server will now forward the contents of the email contained in the envelope, through SMTP and the receiver server will send it to the recipient through POP/IMAP. Voila!

![Getting Started](https://www.oasis-open.org/khelp/kmlm/user_help/html/images/howemailworks.png)

![Getting Started](https://www.howtogeek.com/wp-content/uploads/2011/03/Email-Map.png?trim=1,1&bg-color=000&pad=1,1)



