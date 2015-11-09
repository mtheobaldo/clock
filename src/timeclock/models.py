from __future__ import unicode_literals
from django.db import models
from django.contrib.auth.models import User
import datetime
from django.utils.encoding import python_2_unicode_compatible
import uuid
from django.db import models
from django.conf import settings

def chop_microseconds(delta):
    return delta - datetime.timedelta(microseconds=delta.microseconds)
# Create your models here.
class Project(models.Model):
    title = models.CharField(max_length = 200)

    def __unicode__(self):
        return self.title

class Punch(models.Model):
    user     = models.ForeignKey(settings.AUTH_USER_MODEL)
    project  = models.ForeignKey(Project)
    time_in  = models.DateTimeField(auto_now_add = True)
    time_out = models.DateTimeField(blank=True, null=True)
    note     = models.CharField(max_length = 200, blank=True, null=True)

    def is_clocked_in(self):
        if self.time_out == None:
            return True
        return False



    def duration(self):
        if self.time_out and self.time_in:
            return chop_microseconds(self.time_out - self.time_in)
        else:
            return chop_microseconds(datetime.timedelta())

    def __unicode__(self):
        return "%s (in: %s, out: %s, dur: %s)" % (self.user, str(self.time_in), str(self.time_out), str(self.duration()))
        return "%s (%s)" % (self.user, str(self.duration()))

    class Meta:
        verbose_name_plural = "punches"