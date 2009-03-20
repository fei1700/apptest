#include <stdlib.h>
#include <gst/gst.h>
#include "musicplayer.h"
#include "desktop.h"
#include <QtGui>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/soundcard.h>

/********************************************************************/
#include "MediaInfo.h"
#include "MediaInfoDLL.h"

unsigned int get_bitrate(char* filename)
{
    MediaInfo_New();

//    MediaInfo_Open(handle,filename);
//    MediaInfo_Inform(handle,0);


    return 0;
}
/********************************************************************/

gboolean playbin_bus_callback(GstBus *bus,GstMessage *message,gpointer data)
{
	//g_print ("Got %s message\n", GST_MESSAGE_TYPE_NAME (message));
	switch (GST_MESSAGE_TYPE (message)) 
	{
		case GST_MESSAGE_ERROR: 
		{
			GError *err;
			gchar *debug;
			gst_message_parse_error (message, &err, &debug);
			g_print ("Error: %s\n", err->message);
			g_error_free (err);
			g_free (debug);
			//g_main_loop_quit (loop);
			break;
		}
		case GST_MESSAGE_EOS:
			/* end-of-stream */
			//g_main_loop_quit (loop);
			g_print("end of stream\n");
			break;
		default:
			/* unhandled message */
			break;
	}
	/* we want to be notified again the next time there is a message
	 * * on the bus, so returning TRUE (FALSE means we want to stop watching
	 * * for messages on the bus and our callback should not be called again)
	 * */
	return TRUE;
}
extern MusicPlayer *g_musicplay;

void check_drop_frame(void)
{
	GstElement* osssink;
	GstElement* abin;
	GstElement* vbin;
	GstElement* vratecaps;
	gboolean candrop;

	//get capability
	abin = gst_bin_get_by_name (GST_BIN (g_musicplay->m_playbin), "abin");
	if(abin == NULL)
		return;
	
	osssink = gst_bin_get_by_name (GST_BIN (abin), "audiosink");
	
	g_object_get(G_OBJECT(osssink),"current-drop-frame",&candrop ,NULL);

	g_print("check_frop_frame can drop is %d\n", candrop);
	
	if(candrop)
	{
		//drop frame
		vbin = gst_bin_get_by_name (GST_BIN (g_musicplay->m_playbin), "vbin");
		if(vbin == NULL)
			return;
	
		vratecaps = gst_bin_get_by_name (GST_BIN (vbin), "vratecaps");
	
		g_object_set(G_OBJECT(vratecaps),"caps",
			gst_caps_new_simple("video/x-raw-yuv",
			"framerate", GST_TYPE_FRACTION,1 , 1,NULL),NULL);
		
	}
	
}

gboolean print_position(GstElement *pipeline)
{
	GstFormat fmt = GST_FORMAT_TIME;
	gint64 pos, len;
	if (gst_element_query_position (pipeline, &fmt, &pos)
	&& gst_element_query_duration (pipeline, &fmt, &len)) 
	{
		//g_print ("Time: %" GST_TIME_FORMAT " / %" GST_TIME_FORMAT "\r",
		//GST_TIME_ARGS (pos), GST_TIME_ARGS (len));
		g_print("%ld:%ld\r", GST_TIME_AS_SECONDS(pos),GST_TIME_AS_SECONDS(len));
	
		QString time;
		if(GST_TIME_AS_SECONDS(pos)/60)
		{
            	    	time.append(QString("%1").arg(GST_TIME_AS_SECONDS(pos)/60));
                	time.append(QString(":"));
		}
                time.append(QString("%1").arg(GST_TIME_AS_SECONDS(pos)%60));
		time.append(QString(" / "));
		if(GST_TIME_AS_SECONDS(len)/60)
		{
                	time.append(QString("%1").arg(GST_TIME_AS_SECONDS(len)/60));
                	time.append(QString(":"));
		}
                time.append(QString("%1").arg(GST_TIME_AS_SECONDS(len)%60));

		g_musicplay->m_timelabel->setText(time);
		//g_musicplay->m_timelabel->setText("<font color='red'>your</font>");
		gint64 slidervalue=(pos<<6)/len;
		g_musicplay->m_time_slider->setValue(slidervalue);	
	}
	/* call me again */

	check_drop_frame();
	return TRUE;
}

void ossmixerSetVolume(int volume)
{
	gint fd = open("/dev/mixer", O_RDWR);
	if(fd < 0)
	{
		g_print("open mixer fail!!!\n");
		return;
	}

	if(ioctl(fd, SOUND_MIXER_WRITE_VOLUME, &volume) < 0)
		g_print("mixer ioctl [write volume] fail!!!\n");

	close(fd);
	g_print("volume is %d\n", volume);
}

void MusicPlayer::ossSetVolume(int volume)
{
	//16 level volume
//	int volumetable[16]= {0,1,5,9,15,23,31,47,63,95,127,191,255};
	int volumetable[16]= {0,1,2,4,6,10,14,22,30,46,62,94,126,158,190,255};


	ossmixerSetVolume(volumetable[volume>>4]);
}

//extern void* MediaInfo_New ();

int MusicPlayer::gstinit(void)
{
	g_print("gst ");
//		get_bitrate("/mmc/media/zhou.avi");
//	MediaInfo_New();
		return 0;
  	gst_init (NULL,NULL);
	g_print("init ");

  	GstElement *audiosink, *aibin, *videosink, *auconv;
	GstPad *aupad, *vipad;
	GstBus *bus;

	m_playbin = gst_element_factory_make("zplaybin","playbin");
	if(m_playbin==NULL)
	{
		g_error("Could't create 'playbin' element\n");
		return -1;
	}

//print time
	g_timeout_add(100,(GSourceFunc)print_position,GST_PIPELINE(m_playbin));
//	g_timeout_add(200,(GSourceFunc)check_drop_frame,GST_PIPELINE(m_playbin));

	bus=gst_pipeline_get_bus(GST_PIPELINE(m_playbin));
	gst_bus_add_watch(bus,playbin_bus_callback,NULL);
	gst_object_unref(bus);
        g_print("all initialized!\n");

}

void MusicPlayer::preplayfile()
{
	gchar* uri;
	GstStateChangeReturn ret;

	QString file=m_musicpicture->getCurrentSlideCaption();
		QString filepath_s=m_dirpath;
		filepath_s.append(QString("/"));
		filepath_s.append(file);

   		QByteArray ba = filepath_s.toLatin1();
  		char *filepath_c = ba.data();
	
        //uri=g_strdup_printf("file://%s",filename);
	uri=g_strdup_printf("file://%s",filepath_c);
	g_print("uri= %s\n",uri);
	printf("file path is %s\n",filepath_c);

	ret = gst_element_set_state (m_playbin, GST_STATE_NULL);
        if (ret == GST_STATE_CHANGE_FAILURE) {
                g_printerr ("Failed to set playbin to NULL\n");
        return ;
        }

	ret = gst_element_set_state (m_playbin, GST_STATE_READY);
        if (ret == GST_STATE_CHANGE_FAILURE) {
                g_printerr ("Failed to set playbin to ready\n");
        return ;
        }
	
	g_object_set(m_playbin,"uri",uri,NULL);
        g_free(NULL);
}

void MusicPlayer::playfile()
{
	GstStateChangeReturn ret;

	if(m_pause==false)
		preplayfile();

        ret = gst_element_set_state (m_playbin, GST_STATE_PLAYING);
  	if (ret == GST_STATE_CHANGE_FAILURE) {
    		g_printerr ("Failed to set playbin to PLAYING\n");
    	return ;
  	}

  	ret = gst_element_get_state (m_playbin, NULL, NULL, 30 * GST_SECOND);
  	if (ret == GST_STATE_CHANGE_ASYNC) {
    		g_printerr ("Failed to go to PLAYING in 30 seconds, bailing out\n");
    		return ;
  	} else if (ret != GST_STATE_CHANGE_SUCCESS) {
    		g_printerr ("State change to PLAYING failed\n");
    	return ;
  	}
	m_pause=false;
	g_print("playing...\n");
	
}
void MusicPlayer::pausefile(void)
{
	GstStateChangeReturn ret;	
  	ret = gst_element_set_state(m_playbin, GST_STATE_PAUSED);
  	if (ret == GST_STATE_CHANGE_FAILURE) {
    		g_printerr ("Failed to set playbin to PAUSE\n");
    		return;
  	}
	m_pause=true;
	g_print("paused...\n");
}

extern Desktop *g_desktop;

void MusicPlayer::rotatefile(void)
{
	GstStateChangeReturn ret;
	int rotate = 0;

	GstFormat fmt = GST_FORMAT_TIME;
	gint64 posnow;
	if(gst_element_query_position(m_playbin,&fmt,&posnow)) 
	{

	  	ret = gst_element_set_state(m_playbin, GST_STATE_READY);
	  	if (ret == GST_STATE_CHANGE_FAILURE) {
	    		g_printerr ("Failed to set playbin to READY\n");
	    		return;
	  	}

		if(rotate)
			g_object_set(G_OBJECT(m_playbin), "vflip-none", NULL, NULL);
		else
			g_object_set(G_OBJECT(m_playbin), "vflip-rotate", NULL, NULL);

	  	ret = gst_element_set_state(m_playbin, GST_STATE_PLAYING);
	  	if (ret == GST_STATE_CHANGE_FAILURE) {
	    		g_printerr ("Failed to set playbin to PLAYING\n");
	    		return;
	  	}
	
	  	ret = gst_element_get_state (m_playbin, NULL, NULL, 30 * GST_SECOND);
	  	if (ret == GST_STATE_CHANGE_ASYNC) {
	    		g_printerr ("Failed to go to PLAYING in 30 seconds, bailing out\n");
	    		return ;
	  	} else if (ret != GST_STATE_CHANGE_SUCCESS) {
	    		g_printerr ("State change to PLAYING failed\n");
	    	return ;
	  	}
		
		g_print("gst_element_seek\n");
  		if (!gst_element_seek (m_playbin, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
                         GST_SEEK_TYPE_SET, posnow,
                         GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE))
    			g_print ("Seek failed!\n");
  	}

}

void MusicPlayer::setposition(int pos)
{
	g_print("set position pos= %d\r\n",pos);
	GstFormat fmt = GST_FORMAT_TIME;
	gint64 posnano, posnow,len;
	if(gst_element_query_position(m_playbin,&fmt,&posnow) && 
			gst_element_query_duration (m_playbin, &fmt, &len)) 
	{
		if(pos == ((posnow<<6)/len))
			return;
		posnano=(pos*len)>>6;
  		if (!gst_element_seek (m_playbin, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
                         GST_SEEK_TYPE_SET, posnano,
                         GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE))
    			g_print ("Seek failed!\n");
  	}	
}
