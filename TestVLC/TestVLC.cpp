// TestVLC.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#define  ssize_t int
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include "vlc/vlc.h"

FILE *file = NULL;
 int libvlc_media_open(void *opaque, void **datap,uint64_t *sizep){
	 fopen_s(&file, "../test.f4v", "rb");
	 if (file != NULL){
		 fseek(file, 0, SEEK_END);
		 *sizep = ftell(file);
		 rewind(file);
		 return 0;
	 }
}
 ssize_t libvlc_media_read(void *opaque, unsigned char *buf,size_t len){
	 auto res = fread(buf, 1, len, file);
	 if (res == 0)
		 return feof(file) != 0 ? 0 : -1;
	 return res;
 }
  int libvlc_media_seek(void *opaque, uint64_t offset){
	  if (fseek(file, offset, SEEK_SET) < 0){
		  return -1;
	  }
	return 0;
 }
 void libvlc_media_close(void *opaque){
	 if (file != NULL){
		 fclose(file);
	 }
 }
int _tmain(int argc, char* argv[])
{
	char *ptr = NULL;
	auto instance = libvlc_new(0, nullptr);
	libvlc_media_t *m = libvlc_media_new_callbacks(instance, libvlc_media_open, libvlc_media_read, libvlc_media_seek, libvlc_media_close, NULL);
	libvlc_media_player_t *mp = mp = libvlc_media_player_new_from_media(m);;

	libvlc_media_release(m);
	libvlc_media_player_play(mp);

	Sleep(40000); /* Let it play a bit */
	/* Stop playing */
	libvlc_media_player_stop(mp);

	/* Free the media_player */
	libvlc_media_player_release(mp);
	libvlc_release(instance);

	return 0;
}

void test()
{
	libvlc_instance_t * inst;
	libvlc_media_player_t *mp;
	libvlc_media_t *m;

	const char *vlc_args[] =
	{
		"--ignore-config",
		"--network-caching=500",
		"--rtsp-tcp",
		"--longhelp",
		"--advanced",
	};
	/* Load the VLC engine */
	inst = libvlc_new(0, NULL);

	/* Create a new item */
	m = libvlc_media_new_location(inst, "http://www.jiluzhijia.cn/test.f4v");
	//m = libvlc_media_new_path (inst, "/path/to/test.mov");

	/* Create a media player playing environement */
	mp = libvlc_media_player_new_from_media(m);

	/* No need to keep the media now */
	libvlc_media_release(m);

#if 0
	/* This is a non working code that show how to hooks into a window,
	* if we have a window around */
	libvlc_media_player_set_xwindow(mp, xid);
	/* or on windows */
	libvlc_media_player_set_hwnd(mp, hwnd);
	/* or on mac os */
	libvlc_media_player_set_nsobject(mp, view);
#endif

	/* play the media_player */
	libvlc_media_player_play(mp);

	Sleep(10000); /* Let it play a bit */

	/* Stop playing */
	libvlc_media_player_stop(mp);

	/* Free the media_player */
	libvlc_media_player_release(mp);

	libvlc_release(inst);

}