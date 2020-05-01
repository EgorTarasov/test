from django.db import models


# Create your models here.

class Container(models.Model):
    container_name = models.CharField(
        default=' ',
        max_length=15

    )
    field_status = models.BooleanField(
        default=False,
        help_text='container state',
    )
    field_user = models.CharField(
        default=' ',
        max_length=10
    )

