#include "control_client.h"
#include "gsocket.h"
#include "stdio.h"

struct _ControlClient
{
  gchar *path;
  gint control_socket;
};

ControlClient *
control_client_new(const gchar *name)
{
  ControlClient *self = g_new(ControlClient,1);

  self->path = g_strdup(name);
  self->control_socket = -1;

  return self;
}

gboolean
control_client_connect(ControlClient *self)
{
  GSockAddr *saddr = NULL;

  if (self->control_socket != -1)
    {
      return TRUE;
    }

  saddr = g_sockaddr_unix_new(self->path);
  self->control_socket = socket(PF_UNIX, SOCK_STREAM, 0);

  if (self->control_socket == -1)
    {
      fprintf(stderr, "Error opening control socket, socket='%s', error='%s'\n", self->path, strerror(errno));
      goto error;
    }

  if (g_connect(self->control_socket, saddr) != G_IO_STATUS_NORMAL)
    {
      fprintf(stderr, "Error connecting control socket, socket='%s', error='%s'\n", self->path, strerror(errno));
      close(self->control_socket);
      self->control_socket = -1;
      goto error;
    }
error:
  g_sockaddr_unref(saddr);
  return (self->control_socket != -1);
}

gint
control_client_send_command(ControlClient *self, const gchar *cmd)
{
  return write(self->control_socket, cmd, strlen(cmd));
}

#define BUFF_LEN 8192

GString *
control_client_read_reply(ControlClient *self)
{
  gsize len = 0;
  gchar buff[BUFF_LEN];
  GString *reply = g_string_sized_new(256);

  while (1)
    {
      if ((len = read(self->control_socket, buff, BUFF_LEN - 1)) < 0)
        {
          fprintf(stderr, "Error reading control socket, error='%s'\n", strerror(errno));
          g_string_free(reply, TRUE);
          return NULL;
        }

      if (len == 0)
        {
          fprintf(stderr, "EOF occured while reading control socket\n");
          g_string_free(reply, TRUE);
          return NULL;
        }

      g_string_append_len(reply, buff, len);

      if (reply->str[reply->len - 1] == '\n' &&
          reply->str[reply->len - 2] == '.' &&
          reply->str[reply->len - 3] == '\n')
        {
          g_string_truncate(reply, reply->len - 3);
          break;
        }
    }
  return reply;
}

void
control_client_free(ControlClient *self)
{
  if (self->control_socket != -1)
    {
      shutdown(self->control_socket, SHUT_RDWR);
      close(self->control_socket);
    }
  g_free(self->path);
  g_free(self);
}
