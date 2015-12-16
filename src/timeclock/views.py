from django.shortcuts import render
from django.core.urlresolvers import reverse, reverse_lazy
from django.views.generic import FormView, ListView
from django.utils import timezone
from .forms import PunchInForm, PunchOutForm
from django.http import HttpResponseRedirect
import datetime
from django.conf import settings

from .models import Punch, Project
from django.contrib.auth.models import User


# Create your views here.
class ClockInOutView(FormView):

    def get_template_names(self):
        template_name = 'timeclock/home_clockin.html'
        records = self.request.user.punch_set.order_by('-time_in')
        print records
        if records:
            print "we have records."
            if records[0].is_clocked_in():
                print "record zero says we're clocked in"
                template_name = 'timeclock/home_clockout.html'
            else:
                print "record zero says we're NOT clocked in"
                

        return [template_name]
        

    def get_form_class(self):
        records = self.request.user.punch_set.order_by('-time_in')
        if records:
            if records[0].is_clocked_in():
                return PunchOutForm

        return PunchInForm

    def get_context_data(self, **kwargs):
        context = super(ClockInOutView, self).get_context_data(**kwargs)
        objects = context["last_punch"] = Punch.objects.filter(user = self.request.user).order_by('-time_in')
        if objects:
            context["last_punch"] = objects[0]
        else:
            context["last_punch"] = None
        return context

    def form_valid(self, form):
        if type(form).__name__ == 'PunchInForm':
            entry = Punch()
            entry.project = form.cleaned_data["project"]
            entry.user = self.request.user
            entry.save()
            return HttpResponseRedirect(reverse('timeclock:ko'))

        if type(form).__name__ == 'PunchOutForm':
            entry = self.request.user.punch_set.order_by('-time_in')[0]
            entry.note = form.cleaned_data["note"]
            entry.time_out = timezone.now()
            entry.save()
            return HttpResponseRedirect(reverse('timeclock:ko'))



class PunchListView(ListView):
    model = Punch
    
#class called it ReportView
class ReportView(ListView):
    model = Punch
    paginate_by = 10
    
    def get_queryset(self):
        queryset = Punch.objects.filter(user = self.request.user)
        if self.request.user.is_superuser:
            queryset = Punch.objects.all()

        if self.request.user.is_superuser and "user" in self.request.GET and self.request.GET["user"] != "":
            queryset =queryset.filter(user = self.request.GET.get("user"))
        
        if "project" in self.request.GET and self.request.GET["project"] != "":
            queryset = queryset.filter(project = self.request.GET.get("project"))

        if "time_in" in self.request.GET and self.request.GET["time_in"] != "":
            queryset = queryset.filter(time_in__gte = self.request.GET.get("time_in"))

        if "time_out" in self.request.GET and self.request.GET["time_out"] != "":
            d = datetime.datetime.strptime(self.request.GET.get("time_out"), "%Y-%m-%d")
            d = d + datetime.timedelta(days = 1)
            queryset = queryset.filter(time_in__lte = d)

        if "note" in self.request.GET and self.request.GET["note"] != "":
            queryset = queryset.filter(note__icontains = self.request.GET.get("note"))

        return queryset.order_by('-time_in')

    def get_context_data(self, **kwargs):
        context = super(PunchListView, self).get_context_data(**kwargs)

        context["projects"] = Project.objects.all().order_by('title')
        context["users"] = User.objects.all().order_by('first_name').order_by('username')

        queryset = self.get_queryset()
        
        total_time = datetime.timedelta(0)
        for punch in queryset:
            total_time += punch.duration()

        context["total_time"] = total_time

        return context
            



