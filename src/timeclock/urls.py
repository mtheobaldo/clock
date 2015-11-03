
from django.contrib.auth.decorators import login_required
from django.conf.urls import url
from . import views

urlpatterns = [
   url(r'^clock/$', login_required(views.ClockInOutView.as_view()), name="ko"),
]