
from django.contrib.auth.decorators import login_required
from django.conf.urls import url
from . import views

urlpatterns = [
   url(r'^clock/$', login_required(views.ClockInOutView.as_view()), name="ko"),
   url(r'^punches/$', login_required(views.PunchListView.as_view()), name="punches"),
   url(r'^report/$', login_required(views.ReportView.as_view()), name="report"),

]