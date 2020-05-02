from django.contrib.auth.decorators import login_required
from django.shortcuts import render, redirect
from .models import Container
from django.contrib.auth.forms import UserCreationForm
from django.urls import reverse_lazy
from django.views import generic
import serial
import time
from datetime import datetime


class SignUp(generic.CreateView):
    form_class = UserCreationForm
    success_url = reverse_lazy('login')
    template_name = 'signup.html'


def index(request):
    context = dict()
    containers = Container.objects.all()
    context['containers'] = containers
    return render(request, 'index.html', context)


def container_rent(request, container_id):
    rent(container_id)
    containers = Container.objects.get(pk=container_id)
    containers.field_user = 'user1'
    containers.field_status = 'True'
    containers.save()
    containers = Container.objects.all()
    context = dict()
    context['containers'] = containers
    return redirect('index')


def container_return(request, container_id):
    rent(container_id)
    containers = Container.objects.get(pk=container_id)
    containers.field_user = ''
    containers.field_status = 'False'
    containers.save()
    containers = Container.objects.all()
    context = dict()
    context['containers'] = containers
    return redirect('index')


def rent(container_id):
    arduino = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    arduino.open()
    arduino.write(b"h")
    time.sleep(10)
    arduino.write(b"b")
    if container_id == 1:
        arduino.write(b"f")
    elif container_id == 2:
        arduino.write(b"g")
    elif container_id == 3:
        arduino.write(b"h")
    time.sleep(10)
    if container_id == 1:
        arduino.write(b"c")
    elif container_id == 2:
        arduino.write(b"v")
    elif container_id == 3:
        arduino.write(b"b")

    arduino.close()